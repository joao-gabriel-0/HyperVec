//! TODO: implement __gv_shrink()
//! TODO: Shrink the vector in __gv_pop() after the pop operation is performed (use __gv_shrink())

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "hypervec.h"

// Not meant to be used by the end-user
static inline int __check_size_mul_overflow(size_t x, size_t y) {
    return (x > 0 && y > SIZE_MAX / x) ? -1 : 0;  
}

int __gv_alloc(GVec_t *v, size_t capacity, size_t elem_size) {
    if (NULL == v || capacity <= 0 || elem_size <= 0) {
        return -1;
    }
    if (0 != __check_size_mul_overflow(capacity, elem_size)) {
        return -1;
    }
    // Verify if v->buffer is already allocated
    if (NULL != v->buffer) {
        return -1;
    }    
    v->buffer = calloc(capacity, elem_size);
    
    // Verify if the allocation failed
    if (NULL == v->buffer) {
        return -1;
    }
    v->allocation_size = capacity * elem_size;
    v->elem_size       = elem_size;
    v->capacity        = capacity;
    v->occupied        = 0;

    return 0;
}

int __gv_free(GVec_t *v) {
    if (NULL == v || 0 == v->allocation_size || 0 == v->elem_size) {
        return -1;
    }
    // Verify if the vector was already deallocated, return 0 if so
    else if (NULL == v->buffer && 0 == v->allocation_size && 0 == v->elem_size && 0 == v->capacity && 0 == v->occupied) {
        return 0;
    }
    free(v->buffer);
    v->buffer          = NULL;
    v->allocation_size = 0;
    v->elem_size       = 0;
    v->capacity        = 0;
    v->occupied        = 0;
    
    return 0;
}

int __gv_extend(GVec_t *v, size_t new_capacity) {
    if (NULL == v || 0 == v->allocation_size || 0 == v->elem_size || new_capacity <= 0) {
        return -1;
    }
    // Verify if the v->new allocation_size value is out of bounds
    if (0 != __check_size_mul_overflow(new_capacity, v->elem_size)) {
        return -1;
    }
    size_t new_allocation_size = new_capacity * v->elem_size;

    if (new_allocation_size <= v->allocation_size) {
        return -1;
    }
    void *ret_addr = realloc(v->buffer, new_allocation_size);

    // Verify if the reallocation failed
    if (NULL == ret_addr) {
        return -1;
    }
    else {
        v->buffer = ret_addr;
    }
    // Ensure that v->buffer is **NOT** NULL
    if (NULL == v->buffer) {
        return -1;
    }
    v->allocation_size = new_allocation_size;
    v->capacity = new_capacity;
    // v->elem_size and v->used remain the same

    return 0;
}

int __gv_shrink(void) {   
    return 0;
}

void *__gv_get(GVec_t *v, size_t elem_index) {
    if (NULL == v || 0 == v->allocation_size || 0 == v->elem_size || elem_index > v->capacity) {
        return NULL;
    }
    void *addr = (char *) v->buffer + elem_index * v->elem_size;

    if ((char *) addr > (char *) v->buffer + v->allocation_size) {
        return NULL;
    }
    return addr;
}

int __gv_push(GVec_t *v, void *elem_addr) {
    if (NULL == v || NULL == elem_addr || 0 == v->allocation_size || 0 == v->elem_size) {
        return -1;
    }
    // If the vector is full, extend it
    if (v->occupied == v->capacity) {
        if (__gv_extend(v, v->capacity * __GV_PUSH_REEXTEND_RATE) != 0) {
            return -1;
        }
    }
    // Copy the new element into the vector
    // memcpy((char*) v->buffer + v->occupied * v->elem_size, elem_addr, v->elem_size);    
    memcpy(__gv_get(v, v->occupied), elem_addr, v->elem_size);    
    v->occupied++;

    return 0;
}

int __gv_pop(GVec_t *v, void *dst_addr) {
    if (NULL == v || NULL == v->buffer || 0 == v->allocation_size || 0 == v->elem_size || v->occupied == 0) {
        return -1;
    }

    // Copy the last vector's element to the destination address
    memcpy(dst_addr, __gv_get(v, v->occupied - 1), v->elem_size);
    // memcpy(dst_addr, (char*) v->buffer + (v->occupied - 1) * v->elem_size, v->elem_size);
    v->occupied--;

    return 0;
}

int __gv_iter(GVec_t *v, void (*f)(void*)) {
    if (NULL == v || NULL == v->buffer || NULL ==  f || 0 == v->allocation_size || 0 == v->elem_size || v->occupied == 0) {
        return -1;
    }
    for (size_t i = 0; i < v->capacity; i++) {
        void *addr = __gv_get(v, i);
        (void) f(addr);
    }
    return 0;
}