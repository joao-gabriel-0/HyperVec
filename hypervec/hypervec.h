//! TODO: Implement __gv_shrink()
//! TODO: Implement __gv_remove()
//! TODO: Implement __gv_insert()
//! TODO: Shrink the vector in __gv_pop() after the pop operation is performed (use __gv_shrink())
//! TODO: Implement Numeric Vectors

#ifndef HV_HYPERVEC_H
#define HV_HYPERVEC_H

#include <stddef.h>
#include <stdbool.h>

#define HYPERVEC_VERSION_MAJOR "0"
#define HYPERVEC_VERSION_MINOR "1"

#define HYPERVEC_VERSION HYPERVEC_VERSION_MAJOR "." HYPERVEC_VERSION_MINOR

#define HYPERVEC_RELEASE                                                                        \
    "HyperVec " HYPERVEC_VERSION "\n"                                                           \
    "Copyright (c) 2023 João Gabriel\n"                                                         \
    "This is free software; see the source for copying conditions.\n"                           \
    "There is NO warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n"

/*
gcc (Debian 12.2.0-14) 12.2.0
Copyright (C) 2022 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

// 
// Generic Vectors
// 

typedef struct GVec_s {
    void *buffer;           // Pointer to the allocated memory buffer
    size_t allocation_size; // Total size of the allocated memory buffer
    size_t elem_size;       // Size of each individual element in the buffer
    size_t capacity;        // Number of maximum elements supported by the buffer (given by allocation_size / elem_size) 
    size_t occupied;        // Number of elements currently occupied in the buffer
} GVec_t;

#define gv_alloc(v, capacity, type) \
    __gv_alloc(&v, (capacity), sizeof(type))

int __gv_alloc(GVec_t *v, size_t capacity, size_t elem_size);

#define gv_free(v) \
    __gv_free(&v)

int __gv_free(GVec_t *v);

#define gv_extend(v, new_capacity) \
    __gv_extend(&v, new_capacity)

int __gv_extend(GVec_t *v, size_t new_capacity);

#define gv_shrink(v, new_capacity) \
    __gv_shrink(&v, new_capacity)

int __gv_shrink(GVec_t *v, size_t new_capacity);

#define gv_get(v, elem_index) \
    __gv_get(&v, elem_index)

void *__gv_get(GVec_t *v, size_t elem_index);

#define __GV_PUSH_REEXTEND_RATE 2

#define gv_push(v, elem) \
    __gv_push(&v, &elem)

int __gv_push(GVec_t *v, void *elem_addr);

#define gv_pop(v, dst) \
    __gv_pop(&v, &dst)

#define gv_insert(v, elem) \
    __gv_insert(&v, &elem);

int __gv_insert(GVec_t *v, void* elem);

#define gv_remove(v, dst) \
    __gv_insert(&v, &dst);

int __gv_remove(GVec_t *v, void* dst);

int __gv_pop(GVec_t *v, void *dst_addr);

#define gv_iter(v, f) \
    __gv_iter(&v, f)

int __gv_iter(GVec_t *v, void (*f)(void*));
// 
// Numeric Vectors
// 

typedef struct NVec_s {
    double *buffer;         // Pointer to the allocated memory buffer
    size_t allocation_size; // Total size of the allocated memory buffer
    size_t elem_size;       // Size of each individual element in the buffer
    size_t capacity;        // Number of maximum elements supported by the buffer (given by allocation_size / elem_size) 
    size_t occupied;        // Number of elements currently occupied in the buffer
} NVec_t;

#endif // HV_HYPERVEC_H
