#include "hypervec.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

int vec_alloc(Vec_t *vec, size_t initial_buffer_size, size_t elem_size) {
    if (NULL == vec || 0 == elem_size || elem_size > initial_buffer_size) { 
        return -1; 
    }

    vec->elem_size = elem_size;
    vec->buffer_size = initial_buffer_size;
    vec->used = 0;
    
    if (0 == initial_buffer_size) {
        vec->buffer = NULL;
    }
    else {
        vec->buffer = malloc(initial_buffer_size);
        
        if (NULL == vec->buffer) { 
            return -1; 
        }
    }
    return 0;
}

int vec_free(Vec_t *vec) {
    if (NULL == vec || 0 == vec->buffer_size) { 
        return -1; 
    }
    
    free(vec->buffer);
    vec->buffer      = NULL;
    vec->elem_size   = 0;
    vec->buffer_size = 0;
    vec->used        = 0;
    
    return 0;
}

int vec_resize(Vec_t *vec, size_t new_buffer_size) {
    Vec_t resized_vec;

    if (NULL == vec || 0 == new_buffer_size) {
        return -1;
    }
    
    if (NULL == vec->buffer) {
        return vec_alloc(vec, new_buffer_size, vec->elem_size);
    }

    if (0 != vec_alloc(&resized_vec, new_buffer_size, vec->elem_size)) {
        return -1;
    }
    // copy contents from vec->buffer to resized_vec->buffer
    memcpy(resized_vec.buffer, vec->buffer, vec->used * vec->elem_size);
    
    resized_vec.used = vec->used;

    vec_free(vec);
    *vec = resized_vec;

    return 0;
}

int vec_reset(Vec_t *vec) {
	if (NULL == vec) {
        return -1;
    }
	vec->used = 0;
	
    return 0;
}

void *vec_get(Vec_t *vec, size_t index) {
	if (index >= vec->used || !vec || !vec->buffer) {
		return NULL;
    }
    return (char*) vec->buffer + vec->elem_size * index;
}

int vec_push(Vec_t *vec, void *src) {
	if (NULL == vec || NULL == src) {
        return -1;
    }
    else if (NULL == vec->buffer) {
		vec_alloc(vec, sizeof(src), vec->elem_size);
    }
    
    if (vec->buffer_size <= vec->elem_size * vec->used) {
        // double buffer_size if necessary
		if (0 != vec_resize(vec, vec->used * 2)) {
            return -1;
        }
    }
    memcpy((char*) vec->buffer + vec->elem_size * vec->used, src, vec->elem_size);
	vec->used++;
	
    return 0;
}

int vec_pop(Vec_t *vec, void *dst) {
	if (NULL == vec) {
		return -1;
    }
    else if (NULL == vec->buffer || 0 == vec->used) {
        return 0;
    }
    
    if (NULL != dst) {
        memcpy(dst, vec_get(vec, vec->used - 1), vec->elem_size);
    }
	vec->used--;
	
    return 0;
} 

int vec_remove(Vec_t *vec, size_t index) {
    if (vec == NULL || index >= vec->used) {
        return -1;
    }

    void *element_to_remove = (char*) vec->buffer + (index * vec->elem_size);
    void *next_element = (char*) vec->buffer + ((index + 1) * vec->elem_size);
    
    size_t bytes_to_move = (vec->used - index - 1) * vec->elem_size;

    memmove(element_to_remove, next_element, bytes_to_move);
    vec->used--;

    return 0;
}

