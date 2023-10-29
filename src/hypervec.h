#ifndef __VEC_HEADER
#define __VEC_HEADER

#include <stddef.h>

typedef struct Vec_s {
    void *buffer;
    size_t elem_size;   // sizeof individual elements inside buffer 
    size_t buffer_size; // sizeof buffer
    size_t used;        // amount of elements used inside buffer (i.e. ocupied)
} Vec_t;

// -------------- vec_alloc --------------------------------------------- //

/// @brief allocates a vector of elements with an initial buffer size
int vec_alloc(Vec_t *vec, size_t initial_buffer_size, size_t elem_size);

// -------------- vec_free ---------------------------------------------- //

/// @brief deallocates a vector  
int vec_free(Vec_t *vec);

// -------------- vec_resize -------------------------------------------- //

/// @brief changes the size of a vector
int vec_resize(Vec_t *vec, size_t new_buffer_size);

// -------------- vec_reset --------------------------------------------- //

/// @brief sets the used variable of a vector to 0, effectively reseting it
int vec_reset(Vec_t *vec);

// -------------- vec_get ----------------------------------------------- //

/// @brief retrieves an element from a vector from an specified index
void *vec_get(Vec_t *vec, size_t index);

// -------------- vec_push ----------------------------------------------- //

/// @brief pushes src into vector
int vec_push(Vec_t *vec, void *src);

// -------------- vec_pop ------------------------------------------------ //

/// @brief pops the first element of a vector to dst 
int vec_pop(Vec_t *vec, void *dst);

// -------------- vec_remove --------------------------------------------- //

/// @brief removes an element from a vector at an specific index
int vec_remove(Vec_t *vec, size_t index);

#endif //__VEC_HEADER