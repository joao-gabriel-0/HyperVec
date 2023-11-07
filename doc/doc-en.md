# HyperVec Documentation

This file contains basic information about what each one of the functionalities provided by HyperVec does.

---

## Vector struct definition

The basic building block of HyperVec is the ```Vec_t``` datatype, it is defined as follows:

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
- ``elem_size`` is the size of individual elements inside the buffer (in bytes).
- ``buffer_size`` is the size of the buffer (in bytes).
- ``used`` is the number of occupied elements inside the buffer.

Here, you can choose between declaring a vector ```vec``` as:

``` C
Vec_t vec;
```

or

``` C
struct Vec_s vec;
```

---

## Functions

``vec_alloc`` allocates a vector based on an initial buffer size.
``` C
int vec_alloc(Vec_t *vec, size_t init_buff_size, size_t elem_size);
```
**Parameters**:
- ``vec`` is a pointer to a vector.
- ``init_buff_size`` is the initial buffer allocation size (in bytes).
- ``elem_size`` is the size of every buffer's elements (in bytes).

**Return**:
0 for success, -1 for failure.

**Example:**

Let's say you want to allocate a vector that can initially hold 20 integer numbers:
```C
// first we declare a vector
Vec_t vec1 = {0};

// then we can allocate it based on our desired size
vec_alloc(&vec1, 20*sizeof(int), sizeof(int));
```
