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

#ifndef __VEC_HEADER
#define __VEC_HEADER

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#define vec_get_value(vec_ptr, index, value_type)   \
    *(value_type*) vec_get(vec_ptr, (size_t) index)

typedef struct Vec_s {
    void *buffer;
    size_t elem_size;   // size of individual elements inside the buffer (in bytes)
    size_t buffer_size; // size of the buffer (in bytes)
    size_t used;        // number of elements used inside the buffer (i.e., occupied)
} Vec_t;

/// @brief allocate a vector with an initial buffer size
/// @param vec pointer to a vector
/// @param init_buff_size initial buffer allocation size (in bytes)
/// @param elem_size size of each element inside the buffer (in bytes)
/// @return 0 for success, -1 for failure
int vec_alloc(Vec_t *vec, size_t init_buff_size, size_t elem_size);

/// @brief deallocate a vector
/// @param vec pointer to a vector
/// @return 0 for success, -1 for failure
int vec_free(Vec_t *vec);

/// @brief change the size of a vector
/// @param vec pointer to a vector
/// @param new_buffer_size New buffer allocation size (in bytes)
/// @return 0 for success, -1 for failure
int vec_resize(Vec_t *vec, size_t new_buffer_size);

/// @brief set the 'used' variable of a vector to 0, effectively resetting it
/// @param vec pointer to a vector
/// @return 0 for success, -1 for failure
int vec_reset(Vec_t *vec);

/// @brief push an element 'src' into the vector
/// @param vec pointer to a vector
/// @param src source element
/// @return 0 for success, -1 for failure
int vec_push(Vec_t *vec, void *src);

/// @brief pop the first element of a vector into 'dst'
/// @param vec pointer to a vector
/// @param dst Destination element
/// @return 0 if successful, -1 if failed
int vec_pop(Vec_t *vec, void *dst);

/// @brief remove an element from a vector at a specific index
/// @param vec pointer to a vector
/// @param index index of the desired element
/// @return 0 if successful, -1 if failed
int vec_remove(Vec_t *vec, size_t index);

/// @brief copy the contents of 'src' to 'dst'
/// @param dst pointer to the destination vector
/// @param src pointer to the source vector
/// @return 0 if successful, -1 if failed
int vec_copy(Vec_t *dst, Vec_t *src);

/// @brief append the contents of 'src' to 'dst'
/// @param dst pointer to the destination vector
/// @param src pointer to the source vector
/// @return 0 if successful, -1 if failed
int vec_append(Vec_t *dst, Vec_t *src);

/// @brief prepend the contents of 'src' to 'dst'
/// @param dst pointer to the destination vector
/// @param src pointer to the source vector
/// @return 0 if successful, -1 if failed
int vec_prepend(Vec_t *dst, Vec_t *src);

/// @brief filters out the elements of src and stores them in dst based on a user-defined filter() function
/// @param dst pointer to the destination vector
/// @param src pointer to the source vector
/// @param filter pointer to a filter function 
/// @return 0 if successful, -1 if failed
int vec_filter(Vec_t *dst, Vec_t *src, bool (*filter)(void*));

/// @brief iterates the elements of a vector and calls a user-defined function iter() for each element
/// @param vec pointer to a vector
/// @return 0 if successful, -1 if failed
int vec_iter(Vec_t *vec, void (*iter) (void *));

/// @brief retrieve an element's address from a vector based on a specific index
/// @param vec pointer to a vector
/// @param index Index of the desired element
/// @return address of the desired element
void *vec_get(Vec_t *vec, size_t index);

#endif //__VEC_HEADER
