/*
 * This file is NOT part of the HyperVec Library.
 */

#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <assert.h>
#include <stdio.h>

#include <hypervec.h>

#define One_GB (int64_t) 1e9

// flags for vec_display_info()
#define PRINT_ELEM_SIZE   0x1
#define PRINT_BUFFER_SIZE 0x2
#define PRINT_USED        0x4
#define PRINT_ALL         0xF

#define vec_print(vec, type, fmt)                           \
    printf("[");                                            \
    for (size_t i = 0; i < (vec).used; i++) {               \
        type curr = *(type *) vec_get(&(vec), i);           \
        printf(i+1 == (vec).used ? fmt"]" : fmt", ", curr); \
    } printf("\n")

#define vec_display_info(vec, flags)                                            \
    if (flags & 1) { printf("\telem_size (bytes):   %ld\n", vec.elem_size); }   \
    if (flags & 2) { printf("\tbuffer_size (bytes): %ld\n", vec.buffer_size); } \
    if (flags & 4) { printf("\telements used:       %ld\n", vec.used); }        \
    printf("\n")

#define assert_vec_alloc(vec, buffer_size_val, elem_size_val) \
    assert(NULL            != vec.buffer      );              \
    assert(buffer_size_val == vec.buffer_size );              \
    assert(elem_size_val   == vec.elem_size   );              \
    assert(0               == vec.used        )

#define assert_vec_values(vec, buffer_size_val, elem_size_val, used_val) \
    assert(NULL            != vec.buffer      );                         \
    assert(buffer_size_val == vec.buffer_size );                         \
    assert(elem_size_val   == vec.elem_size   );                         \
    assert(used_val        == vec.used        )

#define assert_vec_free(vec)            \
    assert(NULL == (vec).buffer      ); \
    assert(0    == (vec).buffer_size ); \
    assert(0    == (vec).elem_size   ); \
    assert(0    == (vec).used        )

// filter function for test 12
static bool is_even(void *element) {
    return (*(int *)element % 2 == 0);
}

// filter function for test 13
static void sum_int(void *element) {
    *(int *)element += 1;
}

int main(void) {
    // 
    // test 1: allocate and free vector 
    // 
    Vec_t vec1 = {0};

    assert(0 == vec_alloc(&vec1, One_GB, sizeof(char)));
    assert_vec_alloc(vec1, One_GB, sizeof(char));

    assert(0 == vec_free(&vec1));
    assert_vec_free(vec1);

    // 
    // test 2: allocate, resize, and free a vector
    // 
    struct Vec_s vec2 = {0};

    assert(0 == vec_alloc(&vec2, 10 * sizeof(int), sizeof(int)));
    assert_vec_alloc(vec2, 10 * sizeof(int), sizeof(int));

    assert(0 == vec_resize(&vec2, One_GB * sizeof(int)));
    assert_vec_values(vec2, One_GB * sizeof(int), sizeof(int), 0);

    assert(0 == vec_free(&vec2));
    assert_vec_free(vec2);

    // 
    // test 3: allocate, reset, and free a vector
    // 
    Vec_t vec3 = {0};

    assert(0 == vec_alloc(&vec3, One_GB * sizeof(int), sizeof(int)));
    assert_vec_alloc(vec3, One_GB * sizeof(int), sizeof(int));

    vec3.used = 10;

    assert(0 == vec_reset(&vec3));
    assert_vec_values(vec3, One_GB * sizeof(int), sizeof(int), 0);
    
    assert(0 == vec_free(&vec3));
    assert_vec_free(vec3);

    // 
    // test 4: push some elements to a vector, then pop some after
    // 
    Vec_t vec4 = {0};

    assert(0 == vec_alloc(&vec4, One_GB * sizeof(int), sizeof(int)));
    assert_vec_alloc(vec4, One_GB * sizeof(int), sizeof(int));

    // populate the vector
    for (size_t i = 0; i < 100000; i++) {
        assert(0 == vec_push(&vec4, &i));
    }
    // assert that the vector was susscessfully populated
    for (int i = 0; i < 100000; i++) {
        assert(i == vec_get_value(&vec4, i, int));
    }
    
    int value1 = 42;
    assert(0 == vec_push(&vec4, &value1));
    
    // assert that the popped value is correct
    int popped_value2 = 0;
    assert(0 == vec_pop(&vec4, &popped_value2));
    assert(42 == popped_value2);

    assert(0 == vec_free(&vec4));
    assert_vec_free(vec4);

    //
    // test 5: fetch an element from a vector 
    //
    Vec_t vec5 = {0};

    assert(0 == vec_alloc(&vec5, One_GB * sizeof(int), sizeof(int)));
    assert_vec_alloc(vec5, One_GB * sizeof(int), sizeof(int));
    
    int value2 = 42;
    assert(0 == vec_push(&vec5, &value2));
    
    // assert that the fetched value is correct
    int fetched_value = vec_get_value(&vec5, 0, int);
    assert(fetched_value == 42);

    assert(0 == vec_free(&vec5));
    assert_vec_free(vec5);

    //
    // test 6: remove an element from a vector 
    //
    Vec_t vec6 = {0};

    assert(0 == vec_alloc(&vec6, One_GB * sizeof(int), sizeof(int)));
    assert_vec_alloc(vec6, One_GB * sizeof(int), sizeof(int));

    // populate the vector
    for (size_t i = 0; i < 100; i++) {
        assert(0 == vec_push(&vec6, &i));
    }
    // remove an element from index 42
    assert(0 == vec_remove(&vec6, 42));

    // assert that the vector was sucessfully modified
    for (size_t i = 0; i < vec6.used; i++) {
        if (i < 42) {
            assert((int)i == vec_get_value(&vec6, i, int));
        } else {
            assert((int)(i + 1) == vec_get_value(&vec6, i, int));
        }
    }
    assert(0 == vec_free(&vec6));
    assert_vec_free(vec6);

    //
    // test 7: copy a vector into another (100 * sizeof(int) & sizeof(int) allocation)
    //
    Vec_t vec7 = {0}, vec8 = {0};

    assert(0 == vec_alloc(&vec7, 100 * sizeof(int), sizeof(int)));
    assert_vec_alloc(vec7, 100 * sizeof(int), sizeof(int));
    
    assert(0 == vec_alloc(&vec8, sizeof(int), sizeof(int)));
    assert_vec_alloc(vec8, sizeof(int), sizeof(int));

    for (int i = 0; i < 100; i++) {
        assert(0 == vec_push(&vec7, &i));
    }

    // note that vec8 is much smaller than vec7
    assert(0 == vec_copy(&vec8, &vec7));
    assert(vec7.used == vec8.used);

    for (size_t i = 0; i < vec7.used; i++) {
        int vec7_value = vec_get_value(&vec7, i, int);
        int vec8_value = vec_get_value(&vec8, i, int);
        assert(vec7_value == vec8_value);
    }
    assert(0 == vec_free(&vec7));
    assert_vec_free(vec7);

    assert(0 == vec_free(&vec8));
    assert_vec_free(vec8);

    // 
    // test 8: handling invalid operations
    // 
    Vec_t vec9 = {0};

    int popped_value1 = 0;

    // attempt to pop from a NULL vector
    assert(-1 == vec_pop(NULL, &popped_value1));

    // attempt to pop from an empty unallocated vector (should return 0 and do nothing)
    assert(0 == vec_pop(&vec9, &popped_value1));

    // attempt to remove an element at an index that's out of bounds
    assert(-1 == vec_remove(&vec9, 42));

    // attempt to free an unallocated vector
    assert(-1 == vec_free(&vec9));
    assert_vec_free(vec9);

    //
    // test 9: append two vectors
    //
    Vec_t vec10 = {0}, vec11 = {0};
    
    assert(0 == vec_alloc(&vec10, 10 * sizeof(int), sizeof(int)));
    assert_vec_alloc(vec10, 10 * sizeof(int), sizeof(int));
    
    assert(0 == vec_alloc(&vec11, 10 * sizeof(int), sizeof(int)));
    assert_vec_alloc(vec11, 10 * sizeof(int), sizeof(int));

    // populate both vectors
    for (int i = 0; i < 5; i++) {
        assert(0 == vec_push(&vec10, &i));
    }
    for (int i = 5; i < 10; i++) {
        assert(0 == vec_push(&vec11, &i));
    }

    assert(0 == vec_append(&vec10, &vec11));

    vec_print(vec10, int, "%d");
    vec_display_info(vec10, PRINT_ALL);

    // assert that vec10 contains elements from 0 to 9
    for (int i = 0; i < 10; i++) {
        assert(i == vec_get_value(&vec10, i, int));
    }
    assert(0 == vec_free(&vec10));
    assert_vec_free(vec10);

    assert(0 == vec_free(&vec11));
    assert_vec_free(vec11);

    //
    // test 10: prepend two vectors 
    //
    Vec_t vec12 = {0}, vec13 = {0};

    assert(0 == vec_alloc(&vec12, 10 * sizeof(int), sizeof(int)));
    assert_vec_alloc(vec12, 10 * sizeof(int), sizeof(int));

    assert(0 == vec_alloc(&vec13, 10 * sizeof(int), sizeof(int)));
    assert_vec_alloc(vec13, 10 * sizeof(int), sizeof(int));

    // populate both vectors
    for (int i = 0; i < 5; i++) {
        assert(0 == vec_push(&vec12, &i));
    }
    for (int i = 5; i < 10; i++) {
        assert(0 == vec_push(&vec13, &i));
    }

    assert(0 == vec_prepend(&vec12, &vec13));

    vec_print(vec12, int, "%d");
    vec_display_info(vec12, PRINT_ALL);

    // assert that vec12 contains elements from 5 to 9 followed by elements from 0 to 4
    int expected1[] = {5, 6, 7, 8, 9, 0, 1, 2, 3, 4};
    for (int i = 0; i < 10; i++) {
        assert(expected1[i] == vec_get_value(&vec12, i, int));
    }
    assert(0 == vec_free(&vec12));
    assert_vec_free(vec12);

    assert(0 == vec_free(&vec13));
    assert_vec_free(vec13);

    //
    // test 11: manipulate some strings using dynamic vectors (10 * sizeof(char) allocation)
    //
    Vec_t vec14 = {0};

    assert(0 == vec_alloc(&vec14, 10 * sizeof(char*), sizeof(char*)));
    assert_vec_alloc(vec14, 10 * sizeof(char*), sizeof(char*));

    const char *str1 = "this is";
    const char *str2 = "the power";
    const char *str3 = "of";
    const char *str4 = "dynamic vectors!!!";

    assert(0 == vec_push(&vec14, &str1));
    assert(0 == vec_push(&vec14, &str2));
    assert(0 == vec_push(&vec14, &str3));
    assert(0 == vec_push(&vec14, &str4));

    vec_print(vec14, char*, "\"%s\"");
    vec_display_info(vec14, PRINT_ALL);
    
    char *retrieved_str1 = vec_get_value(&vec14, 0, char*);
    char *retrieved_str2 = vec_get_value(&vec14, 1, char*);
    char *retrieved_str3 = vec_get_value(&vec14, 2, char*);
    char *retrieved_str4 = vec_get_value(&vec14, 3, char*);

    assert(0 == strcmp(retrieved_str1, str1));
    assert(0 == strcmp(retrieved_str2, str2));
    assert(0 == strcmp(retrieved_str3, str3));
    assert(0 == strcmp(retrieved_str4, str4));

    char *popped_str = NULL;
    assert(0 == vec_pop(&vec14, &popped_str));

    printf("popped string: %s\n", popped_str);

    vec_free(&vec14);
    assert_vec_free(vec14);

    //
    // test 12: filter elements from a vector that aren't even
    //
    Vec_t vec15 = {0}, vec16 = {0};

    assert(0 == vec_alloc(&vec15, 25 * sizeof(int), sizeof(int)));
    assert_vec_alloc(vec15, 25 * sizeof(int), sizeof(int));

    assert(0 == vec_alloc(&vec16, 100 * sizeof(int), sizeof(int)));
    assert_vec_alloc(vec16, 100 * sizeof(int), sizeof(int));

    for (int i = 0; i < 25; i++) {
        assert(0 == vec_push(&vec15, &i));
    }
    // filter even numbers from vec15 to vec16 
    assert(0 == vec_filter(&vec16, &vec15, is_even));

    printf("filtered elements from vec15 to vec16: ");
    vec_print(vec16, int, "%d");

    // assert that the filtered elements are even
    for (size_t i = 0; i < vec16.used; i++) {
        int *num = (int *)vec_get(&vec16, i);
        assert(0 == *num % 2);
    }
    assert(0 == vec_free(&vec15));
    assert_vec_free(vec15);

    assert(0 == vec_free(&vec16));
    assert_vec_free(vec16);

    //
    // test 13: iterate a vector
    //
    Vec_t vec17 = {0};

    assert(0 == vec_alloc(&vec17, 25 * sizeof(int), sizeof(int)));
    assert_vec_alloc(vec17, 25 * sizeof(int), sizeof(int));

    for (int i = 0; i < 25; i++) {
        assert(0 == vec_push(&vec17, &i));
    }
    printf("original vector: ");
    vec_print(vec17, int, "%d");

    assert(0 == vec_iter(&vec17, sum_int));

    printf("iterated vector: ");
    vec_print(vec17, int, "%d");

    // assert that the iterated elements were incremented
    for (size_t i = 0; i < vec17.used; i++) {
        int *num = (int *)vec_get(&vec17, i);
        assert((int) i == (*num) - 1);
    }

    assert(0 == vec_free(&vec17));
    assert_vec_free(vec17);

    printf("all tests succeded\n");

    return 0;
}
