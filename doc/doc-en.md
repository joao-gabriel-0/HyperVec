# Hypervec

A public Open-Source Library for Safely Handling Dynamic Vector Operations in C

---

## How to read this documentation?

### Vector Types

This documentation is divided into 2 parts, **Generic Vectors** and **Numeric Vectors**.

Generic Vectors represent one-dimensional dynamic arrays designed to accommodate a sequence of arbitrary (`void*`) addresses. These vectors are specifically crafted for scenarios demanding the storage and manipulation of diverse data types within a linear structure of indefinite length.

Numeric Vectors, on the other hand, are one-dimensional arrays engineered to hold a sequence of double numbers. Devoid of a predefined length, these vectors are designed to support mathematical operations, like: normalization, sorting, dot product, convolution, etc.

### Feature State Indicators

Feature State Indicators (FSI) are represented by color-coded boxes to communicate the status of a feature, categorizing it as either _coming up_, _experimental_, _unstable_, or _deprecated_:

- <span style="border-radius:5px; padding:2px; background-color:rgb(255, 165, 0); color:rgb(240, 240, 240)">Coming Soon</span>: This indicator signifies that a feature is currently in development and will be released in the near future.

- <span style="border-radius:5px; padding:2px; background-color:rgb(52, 152, 219); color:rgb(240, 240, 240)">Experimental</span>: This designation indicates that a particular feature is in an experimental phase, with its inclusion as an official feature in upcoming releases subject to further evaluation.

- <span style="border-radius:5px; padding:2px; background-color:rgb(181, 197, 38); color:rgb(240, 240, 240)">Unstable</span>: Features labeled as "Unstable" are deemed not yet suitable for production environments, posing potential risks to end-users.

- <span style="border-radius:5px; padding:2px; background-color:rgb(220, 20, 60); color:rgb(240, 240, 240)">Deprecated</span>: A "Deprecated" status indicates that a specific feature is no longer supported and has been removed from the library.

Features that aren't marked with an FSI are already supported by the library.

---

## Generic Vectors

### Basic Generic Vector Structure

```c
typedef struct GVec_s {
    void *buffer;
    size_t allocation_size;
    size_t elem_size;
    size_t capacity; 
    size_t occupied;
} GVec_t;
```

### Generic Vector Manipulation Functions

#### gv_alloc()

```c
#define gv_alloc(v, capacity, type) \
    __gv_alloc(&v, (capacity), sizeof(type))
int __gv_alloc(GVec_t *v, size_t capacity, size_t elem_size);
```

#### gv_free()

```c
#define gv_free(v) \
    __gv_free(&v)

int __gv_free(GVec_t *v);
```

#### gv_extend()

```c
#define gv_extend(v, new_capacity) \
    __gv_extend(&v, new_capacity)

int __gv_extend(GVec_t *v, size_t new_capacity);
```

#### gv_shrink() <span style="border-radius:5px; padding:2px; background-color:rgb(255, 165, 0); color:rgb(240, 240, 240)">Coming Soon</span>

```c
#define gv_shrink(v, new_capacity) \
    __gv_shrink(&v, new_capacity)

int __gv_shrink(GVec_t *v, size_t new_capacity);
```

#### gv_get()

```c
#define gv_get(v, elem_index) \
    __gv_get(&v, elem_index)

void *__gv_get(GVec_t *v, size_t elem_index);
```

#### gv_push()

```c
#define __GV_PUSH_REEXTEND_RATE 2
```

```c
#define gv_push(v, elem) \
    __gv_push(&v, &elem)

int __gv_push(GVec_t *v, void *elem_addr);
```

#### gv_pop()

```c
#define gv_pop(v, dst) \
    __gv_pop(&v, &dst)

int __gv_pop(GVec_t *v, void *dst_addr);
```

#### gv_insert() <span style="border-radius:5px; padding:2px; background-color:rgb(255, 165, 0); color:rgb(240, 240, 240)">Coming Soon</span>

```c
#define gv_insert(v, elem) \
    __gv_insert(&v, &elem);

int __gv_insert(GVec_t *v, void* elem);
```

#### gv_remove() <span style="border-radius:5px; padding:2px; background-color:rgb(255, 165, 0); color:rgb(240, 240, 240)">Coming Soon</span>

```c
#define gv_remove(v, dst) \
    __gv_insert(&v, &dst);

int __gv_remove(GVec_t *v, void* dst);
```

#### gv_iter()

```c
#define gv_iter(v, f) \
    __gv_iter(&v, f)

int __gv_iter(GVec_t *v, void (*f)(void*));
```

---

## Numeric Vectors

### Basic Numeric Vector Structure

### Numeric Vector Manipulation Functions
