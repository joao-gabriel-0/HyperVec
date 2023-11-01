# HyperVec

A public open-source library for optimizing dynamic vector operations in C 

HyperVec is a powerful and efficient open-source library designed to optimize dynamic vector operations in the C programming language. It is tailored to provide high performance and versatility for handling dynamically resizable arrays, making it a valuable tool for a wide range of applications. Whether you are working on scientific simulations, data processing, or any C-based project that requires dynamic arrays, HyperVec can help you achieve better performance and productivity.

## Key Features
- **Dynamic Resizing**: HyperVec simplifies dynamic array resizing, ensuring you can effortlessly adapt to changing data requirements. Whether you need to expand or shrink your vectors, HyperVec's intuitive functions make it a breeze.

- **High Performance**: HyperVec ensures efficient performance for your dynamic vector operations in C, allowing you to make the most of your code. 

- **Easy-to-Use API**: HyperVec's user-friendly API streamlines your coding experience. With intuitive design, you'll find it easy to integrate HyperVec into your project, saving you time and effort.

### TODO:

Add contributors

Add the following functionalities:

- vec_from 
- vec_copy  
- vec_insert 
- vec_append 
- vec_prepend 
- vec_iter 
- vec_find 
- vec_map 
- vec_filter 
- vec_reduce 
- vec_sort 

---

# Documentation

This file contains basic information about what each one of the functions provided by ``src/hypervec.h`` does.

## Vector definition

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
- ``elem_size`` is the size (in bytes) of each element within the vector.
- ``buffer_size`` is the total size (in bytes) of the memory buffer allocated for the vector.
- ``used`` is the number of elements populated with values inside the buffer

## Functionalities

``vec_alloc`` is the initializator for every vector, it allocates memory for a vector's buffer and sets each variable inside it with the adequate value.
``` C
int vec_alloc(Vec_t *vec, size_t init_buff_size, size_t elem_size);
```
**parameters**:
- ``vec`` pointer to a vector.
- ``init_buff_size`` initial buffer's allocation size (bytes).
- ``elem_size`` size of each element inside the buffer (bytes).

**return**: 
- 0 if the allocation succeded | -1 if it failed for some reason

# TEMPLATE (escreva em ingles)

``<NOME DA FUNÇÃO>`` breve descrição do que ela faz.
``` C
cabeça (definição) da função (todas estão dentro de hypervec.h)
```

**parameters**:
- ``parametro 1`` descrição do que ele é.
- ``parametro 2`` descrição do que ele é.

**return**: 
- retorno da função

# Contributors
