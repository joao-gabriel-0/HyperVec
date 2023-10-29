#include <stdio.h>
#include <assert.h>

#include "../src/hypervec.h"

int main(int argc, char const *argv[]) {
    // test 1: allocate and free vector
    Vec_t vec1;
        
    assert(0 == vec_alloc(&vec1, (long long int)1e9 * sizeof(char), sizeof(char)));
    assert(0 == vec_free(&vec1));

    assert(NULL == vec1.buffer);
    assert(0 == vec1.buffer_size);
    assert(0 == vec1.elem_size);
    assert(0 == vec1.used);

    // test 2: ensure that all vector's elements have the proper size when allocated
    Vec_t vec2;
    
    typedef struct {
        double a;
        float b;
        int c;
        char d;
        char *e;
    } random_struct_t;

    assert(0 == vec_alloc(&vec2, (long long int)1e9, sizeof(random_struct_t)));

    assert(vec2.buffer_size == (long long int)1e9);
    assert(vec2.elem_size == sizeof(random_struct_t));
    assert(vec2.used == 0);

    assert(0 == vec_free(&vec2));

    // test 3: create, resize, and free a vector
    Vec_t vec3;

    assert(0 == vec_alloc(&vec3, 10 * sizeof(int), sizeof(int)));
    assert(0 == vec_resize(&vec3, (long long int)1e9 * sizeof(int)));

    assert(0 == vec_free(&vec3));

    // test 4: create, reset, and free a vector
    Vec_t vec4;

    assert(0 == vec_alloc(&vec4, (long long int)1e9 * sizeof(int), sizeof(int)));
    assert(0 == vec_reset(&vec4));
    assert(vec4.used == 0);

    assert(0 == vec_free(&vec4));

    // test 5: push some elements to a vector
    Vec_t vec5;
    assert(0 == vec_alloc(&vec5, (long long int)1e9 * sizeof(int), sizeof(int)));

    for (int i = 0; i < 100000; i++) {
        assert(0 == vec_push(&vec5, &i));
    }
    assert(0 == vec_free(&vec5));

    // test 6: pop some elements from a vector
    Vec_t vec6;

    assert(0 == vec_alloc(&vec6, (long long int)1e9 * sizeof(int), sizeof(int)));
    int value1 = 42;
    assert(0 == vec_push(&vec6, &value1));
    int popped_value;
    assert(0 == vec_pop(&vec6, &popped_value));
    assert(popped_value == 42);

    assert(0 == vec_free(&vec6));

    // test 7: fetch an element from a vector
    Vec_t vec7;

    assert(0 == vec_alloc(&vec7, (long long int)1e9 * sizeof(int), sizeof(int)));
    int value2 = 42;
    assert(0 == vec_push(&vec7, &value2));
    int retrieved_value = *(int *)vec_get(&vec7, 0);
    assert(retrieved_value == 42);

    assert(0 == vec_free(&vec7));

    // test 8: remove an element from a vector
    Vec_t vec8;

    assert(0 == vec_alloc(&vec8, (long long int)1e9 * sizeof(int), sizeof(int)));

    for (size_t i = 0; i < 100; i++) {
        assert(0 == vec_push(&vec8, &i));
    }

    size_t index_to_remove = 42;
    assert(0 == vec_remove(&vec8, index_to_remove));

    for (size_t i = 0; i < vec8.used; i++) {
        if (i < index_to_remove) {
            assert((int)i == *(int *)vec_get(&vec8, i));
        } else {
            assert((int)(i + 1) == *(int *)vec_get(&vec8, i));
        }
    }

    assert(0 == vec_free(&vec8));

    return 0;
}
