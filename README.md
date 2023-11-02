<img src="img/hypervec_logo.png" style="width: 100%; height: auto;">

A public Open-Source Library for Safely Handling Dynamic Vector Operations in C

---

HyperVec is a powerful and efficient open-source library designed to optimize dynamic vector operations in the C programming language while prioritizing safety. It is tailored to provide high performance and versatility for handling dynamically resizable arrays, making it a valuable tool for a wide range of applications. Whether you are working on scientific simulations, data processing, or any C-based project that requires dynamic arrays, HyperVec can help you achieve better performance and productivity.

## Key Features
- **Dynamic Resizing**: HyperVec simplifies dynamic array resizing, ensuring you can effortlessly adapt to changing data requirements. Whether you need to expand or shrink your vectors, HyperVec's intuitive functions make it a breeze.

- **High Performance**: HyperVec ensures efficient performance for your dynamic vector operations in C, allowing you to make the most of your code.

- **Easy-to-Use API**: HyperVec's user-friendly API streamlines your coding experience. With intuitive design, you'll find it easy to integrate HyperVec into your project, saving you time and effort.

---

# Documentation

This section contains basic information about what each one of the functions provided by ``src/hypervec.h`` does.

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

---

# Contributors

### TODO:

- Add contributors

- Add the following functionalities:
    - vec_from 
    - vec_insert 
    - vec_iter 
    - vec_find 
    - vec_map 
    - vec_filter 
    - vec_reduce 
    - vec_sort 
