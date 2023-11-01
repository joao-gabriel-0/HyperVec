#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "../src/hypervec.h"

#define One_GigaByte (int64_t) 1e9

int main(void) {
    // 
    // test 1: allocate and free vector (1*10^9 * sizeof(int) allocation)
    // 
    Vec_t vec1 = {0};

    assert(0 == vec_alloc(vec1, One_GigaByte, char));

    assert(NULL != vec1.buffer);
    assert(One_GigaByte == vec1.buffer_size);
    assert(sizeof(char) == vec1.elem_size);
    assert(0 == vec1.used);

    assert(0 == vec_free(&vec1));

    assert(NULL == vec1.buffer);
    assert(0 == vec1.buffer_size);
    assert(0 == vec1.elem_size);
    assert(0 == vec1.used);

    // 
    // test 2: assert that all vector's elements have the proper size when allocated (1*10^9 * sizeof(int) allocation)
    // 
    Vec_t vec2 = {0};
    
    typedef struct {
        double a;
        float b;
        int c;
        char d;
        char *e;
    } random_struct_t;

    assert(0 == vec_alloc(vec2, One_GigaByte, random_struct_t));

    assert(One_GigaByte == vec2.buffer_size);
    assert(sizeof(random_struct_t) == vec2.elem_size);
    assert(0 == vec2.used);

    assert(0 == vec_free(&vec2));

    // 
    // test 3: allocate, resize, and free a vector
    // 
    Vec_t vec3 = {0};

    assert(0 == vec_alloc(vec3, 10 * sizeof(int), int));
    assert(0 == vec_resize(&vec3, One_GigaByte * sizeof(int)));

    assert(0 == vec_free(&vec3));

    // 
    // test 4: allocate, reset, and free a vector
    // 
    Vec_t vec4 = {0};

    assert(0 == vec_alloc(vec4, One_GigaByte * sizeof(int), int));
    assert(0 == vec_reset(&vec4));
    assert(vec4.used == 0);

    assert(0 == vec_free(&vec4));

    // 
    // test 5: push some elements to a vector (1*10^9 * sizeof(int) allocation)
    // 
    Vec_t vec5 = {0};

    assert(0 == vec_alloc(vec5, One_GigaByte * sizeof(int), int));

    // populate the vector
    for (size_t i = 0; i < 100000; i++) {
        assert(0 == vec_push(&vec5, &i));
    }
    // assert that the vector was susscessfully populated
    for (int i = 0; i < 100000; i++) {
        assert(i == vec_get_value(vec5, i, int));
    }
    assert(0 == vec_free(&vec5));
    
    // 
    // test 6: pop some elements from a vector (1*10^9 * sizeof(int) allocation)
    // 
    Vec_t vec6 = {0};

    assert(0 == vec_alloc(vec6, One_GigaByte * sizeof(int), int));
    
    int value1 = 42;
    assert(0 == vec_push(&vec6, &value1));
    
    // assert that the popped value is correct
    int popped_value;
    assert(0 == vec_pop(&vec6, &popped_value));
    assert(popped_value == 42);

    assert(0 == vec_free(&vec6));

    //
    // test 7: fetch an element from a vector (1*10^9 * sizeof(int) allocation)
    //
    Vec_t vec7 = {0};

    assert(0 == vec_alloc(vec7, One_GigaByte * sizeof(int), int));
    
    int value2 = 42;
    assert(0 == vec_push(&vec7, &value2));
    
    // assert that the pushed value is correct
    int retrieved_value = vec_get_value(vec7, 0, int);
    assert(retrieved_value == 42);

    assert(0 == vec_free(&vec7));

    //
    // test 8: remove an element from a vector (1*10^9 * sizeof(int) allocation)
    //
    Vec_t vec8 = {0};

    assert(0 == vec_alloc(vec8, One_GigaByte * sizeof(int), int));

    // populate the vector
    for (size_t i = 0; i < 100; i++) {
        assert(0 == vec_push(&vec8, &i));
    }
    // remove an element
    size_t index_to_remove = 42;
    assert(0 == vec_remove(&vec8, index_to_remove));

    // assert that the vector was sucessfully modified
    for (size_t i = 0; i < vec8.used; i++) {
        if (i < index_to_remove) {
            assert((int)i == vec_get_value(vec8, i, int));
        } else {
            assert((int)(i + 1) == vec_get_value(vec8, i, int));
        }
    }
    assert(0 == vec_free(&vec8));

    //
    // test 9: copy a vector into another (100 * sizeof(int) & sizeof(int) allocation)
    //
    Vec_t vec9 = {0}, vec10 = {0};

    assert(0 == vec_alloc(vec9, 100 * sizeof(int), int));
    assert(0 == vec_alloc(vec10, 1 * sizeof(int), int));

    for (int i = 0; i < 100; i++) {
        assert(0 == vec_push(&vec9, &i));
    }

    // note that vec10 is much smaller than vec9
    assert(0 == vec_copy(&vec10, &vec9));

    assert(vec9.used == vec10.used);

    for (size_t i = 0; i < vec9.used; i++) {
        int vec9_value = vec_get_value(vec9, i, int);
        int vec10_value = vec_get_value(vec10, i, int);
        assert(vec9_value == vec10_value);
    }
    assert(0 == vec_free(&vec9));
    assert(0 == vec_free(&vec10));

    //
    // test 10: append two vectors (both 10 * sizeof(int) allocation)
    //
    Vec_t vec11 = {0}, vec12 = {0};
    
    assert(0 == vec_alloc(vec11, 10 * sizeof(int), int));
    assert(0 == vec_alloc(vec12, 10 * sizeof(int), int));

    // populate both vectors
    for (int i = 0; i < 5; i++) {
        assert(0 == vec_push(&vec11, &i));
    }
    for (int i = 5; i < 10; i++) {
        assert(0 == vec_push(&vec12, &i));
    }

    assert(0 == vec_append(&vec11, &vec12));

    VEC_PRINT(vec11, int, "%d")

    // assert that vec11 contains elements from 0 to 9
    for (int i = 0; i < 10; i++) {
        assert(i == vec_get_value(vec11, i, int));
    }
    assert(0 == vec_free(&vec11));
    assert(0 == vec_free(&vec12));

    //
    // test 11: prepend two vectors (both 10 * sizeof(int) allocation)
    //
    Vec_t vec13 = {0}, vec14 = {0};

    assert(0 == vec_alloc(vec13, 10 * sizeof(int), int));
    assert(0 == vec_alloc(vec14, 10 * sizeof(int), int));

    // populate both vectors
    for (int i = 0; i < 5; i++) {
        assert(0 == vec_push(&vec13, &i));
    }
    for (int i = 5; i < 10; i++) {
        assert(0 == vec_push(&vec14, &i));
    }

    assert(0 == vec_prepend(&vec13, &vec14));

    VEC_PRINT(vec13, int, "%d")

    // assert that vec13 contains elements from 5 to 9 followed by elements from 0 to 4
    int expected1[] = {5, 6, 7, 8, 9, 0, 1, 2, 3, 4};
    for (int i = 0; i < 10; i++) {
        assert(expected1[i] == vec_get_value(vec13, i, int));
    }
    assert(0 == vec_free(&vec13));
    assert(0 == vec_free(&vec14));

    //
    // test 12: manipulate some strings using dynamic vectors (10 * sizeof(char) allocation)
    //
    Vec_t vec15 = {0};

    assert(0 == vec_alloc(vec15, 10 * sizeof(char*), char*));

    const char *str1 = "this is";
    const char *str2 = "the power";
    const char *str3 = "of";
    const char *str4 = "dynamic vectors!!!";

    assert(0 == vec_push(&vec15, &str1));
    assert(0 == vec_push(&vec15, &str2));
    assert(0 == vec_push(&vec15, &str3));
    assert(0 == vec_push(&vec15, &str4));

    VEC_PRINT(vec15, char*, "\"%s\"")

    char *retrieved_str1 = vec_get_value(vec15, 0, char*);
    char *retrieved_str2 = vec_get_value(vec15, 1, char*);
    char *retrieved_str3 = vec_get_value(vec15, 2, char*);
    char *retrieved_str4 = vec_get_value(vec15, 3, char*);

    assert(0 == strcmp(retrieved_str1, str1));
    assert(0 == strcmp(retrieved_str2, str2));
    assert(0 == strcmp(retrieved_str3, str3));
    assert(0 == strcmp(retrieved_str4, str4));

    char *popped_str = NULL;
    assert(0 == vec_pop(&vec15, &popped_str));

    printf("popped string: %s\n", popped_str);

    return 0;
}


