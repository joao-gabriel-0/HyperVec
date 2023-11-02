# Documentation

This file contains basic information about what each one of the functionalities provided by HyperVec does.

## Vector struct definition

``` C
typedef struct Vec_s {
    void *buffer;
    size_t elem_size;
    size_t buffer_size;
    size_t used;
} Vec_t;
```

Where:
- ``buffer`` is a pointer to memory where the vector's elements are stored.
- ``elem_size`` is the size of individual elements inside the buffer (in bytes)
- ``buffer_size`` is the size of the buffer (in bytes)
- ``used`` is the number of elements used inside the buffer (i.e., occupied)

## Functions

``vec_alloc`` is the initializator for every vector, it allocates a vector with an initial buffer size.
``` C
int vec_alloc(Vec_t *vec, size_t init_buff_size, size_t elem_size);
```
**parameters**:
- ``vec`` pointer to a vector
- ``init_buff_size`` initial buffer allocation size (in bytes)
- ``elem_size`` size of each element inside the buffer (in bytes)

**return**:
0 for success, -1 for failure
