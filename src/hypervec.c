/*
 * MIT License
 * Copyright (c) 2023 João Gabriel
 * 
 * This file is part of the HyperVec Library.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS," WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "hypervec.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static int is_null(void *ptr) {
    return NULL == ptr;
}

int vec_alloc(Vec_t *vec, size_t init_buff_size, size_t elem_size) {
    if (is_null(vec) || 0 == elem_size) { 
        return -1; 
    }
    // allocate the vector's buffer and set each variable acording to their respective values
    vec->elem_size   = elem_size;
    vec->buffer_size = init_buff_size;
    vec->used        = 0;
    
    if (0 == init_buff_size) {
        vec->buffer = NULL;
    }
    else {
        vec->buffer = malloc(init_buff_size);
        
        if (is_null(vec->buffer)) { 
            return -1; 
        }
    }
    return 0;
}

int vec_free(Vec_t *vec) {
    if (is_null(vec) || 0 == vec->buffer_size) { 
        return -1; 
    }
    // free the vector's buffer and reset every variable
    free(vec->buffer);
    vec->buffer      = NULL;
    vec->elem_size   = 0;
    vec->buffer_size = 0;
    vec->used        = 0;
    
    return 0;
}

int vec_resize(Vec_t *vec, size_t new_buffer_size) {
    Vec_t resized_vec = {0};

    if (is_null(vec) || 0 == new_buffer_size) {
        return -1;
    }
    if (is_null(vec->buffer)) {
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
	if (is_null(vec)) { 
        return -1; 
    }
    vec->used = 0;
	
    return 0;
}

int vec_push(Vec_t *vec, void *src) {
	if (is_null(vec) || is_null(src)) {
        return -1;
    }
    else if (is_null(vec->buffer)) {
		vec_alloc(vec, sizeof(src) * vec->elem_size, vec->elem_size);
    }

    if (vec->buffer_size <= (vec->elem_size * (vec->used + 1))) {
        if (0 != vec_resize(vec, 2 * vec->buffer_size)) { 
            return -1; 
        }
    }
    // push the new element into the top of the vector's buffer
    memcpy((char*) vec->buffer + vec->elem_size * vec->used, src, vec->elem_size);
    vec->used++;
	
    return 0;
}

int vec_pop(Vec_t *vec, void *dst) {
	if (is_null(vec)) {
		return -1;
    }
    else if (is_null(vec->buffer) || 0 == vec->used) {
        return 0;
    }
    // remove the topmost vector buffer's element 
    memcpy(dst, vec_get(vec, vec->used - 1), vec->elem_size);
    vec->used--;
	
    return 0;
} 

int vec_remove(Vec_t *vec, size_t index) {
    if (is_null(vec) || index >= vec->used) {
        return -1;
    }
    void *element_to_remove = (char*) vec->buffer + (index * vec->elem_size);
    void *next_element      = (char*) vec->buffer + ((index + 1) * vec->elem_size);
    size_t bytes_to_move    = (vec->used - index - 1) * vec->elem_size;

    // move the already occupied memory forward 
    memmove(element_to_remove, next_element, bytes_to_move);
    vec->used--;

    return 0;
}

int vec_copy(Vec_t *dst, Vec_t *src) {
    if (is_null(dst) || is_null(src) || NULL == src->buffer) {
        return -1;
    }
    else if (is_null(dst->buffer) || dst->buffer_size < src->used * src->elem_size) {
        size_t new_buffer_size = src->used * src->elem_size;

        if (0 != vec_resize(dst, new_buffer_size)) {
            return -1;
        }
    }
    // copy the elements from src to dst
    memcpy(dst->buffer, src->buffer, src->used * src->elem_size);
    dst->used = src->used;

    return 0;
}

int vec_append(Vec_t *dst, Vec_t *src) {
    if (is_null(dst) || is_null(src) || dst->elem_size != src->elem_size) {
        return -1;
    }
    size_t new_size = dst->used + src->used;

    if (dst->buffer_size < new_size) {
        if (0 != vec_resize(dst, new_size)) {
            return -1;
        }
    }
    // copy the elements from the src vector to the dst vector
    memcpy((char*) dst->buffer + dst->used * dst->elem_size, src->buffer, src->used * src->elem_size);
    dst->used = new_size;

    return 0;
}

int vec_prepend(Vec_t *dst, Vec_t *src) {
    if (is_null(dst) || is_null(src) || dst->elem_size != src->elem_size) {
        return -1;
    }
    size_t new_size = dst->used + src->used;

    if (dst->buffer_size < new_size) {
        if (0 != vec_resize(dst, new_size)) {
            return -1;
        }
    }
    // move the elements from the dst vector forward to make space for the src vector data
    memmove((char*) dst->buffer + src->used * dst->elem_size, dst->buffer, dst->used * dst->elem_size);

    // copy the elements of the src vector to the beginning of the dst vector
    memcpy(dst->buffer, src->buffer, src->used * src->elem_size);
    // update the used variable based on the previous size + new size
    dst->used = new_size;

    return 0;
}

int vec_filter(Vec_t *dst, Vec_t *src, bool (*filter)(void*)) {
    void *ptr;
    void *res;

    if (is_null(dst) || is_null(src) || is_null(src->buffer)) {
        return -1;
    } 
    else if (is_null(dst->buffer)) {
        if (0 != vec_alloc(dst, 1, dst->elem_size)) { 
            return -1; 
        }
    }
    res = malloc(dst->elem_size);
    
    if (is_null(res)) { 
        return -1; 
    }

    // populate the dst vector based on the result of the filter iteration function 
    for (size_t i = 0; i < src->used; i++) {
        ptr = vec_get(src, i);
        if (is_null(ptr)) { 
            return -1; 
        }
            
        memcpy(res, ptr, dst->elem_size);

        if (filter(res)) {
            if (0 != vec_push(dst, res)) { 
                free(res); 
                return -1; 
            }
        }
    }
    free(res);
    
    return 0;
}

int vec_iter(Vec_t *vec, void (*iter) (void *)) {
	void *ptr;

	if (is_null(vec) || is_null(vec->buffer)) {
		return -1; 
    }
	
    // iterate each element, calling the iter function as desired
	for (size_t i = 0; i < vec->used; i++) {
		ptr = vec_get(vec, i);
		iter(ptr);
	}
    return 0;
}

void *vec_get(Vec_t *vec, size_t index) {
	if (is_null(vec) || index >= vec->used || is_null(vec->buffer)) {
		return NULL;
    }
    // return the element's address at the desired index
    return (char*) vec->buffer + vec->elem_size * index;
}

