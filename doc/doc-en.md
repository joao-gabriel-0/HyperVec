# HyperVec Documentation

This file provides information about the functionalities of HyperVec, presented in the order defined in the "Hypervec.h" file.

---

## Definition of the vector structure

The fundamental element of HyperVec is the data type `Vec_t`, defined as follows in "Hypervec.h":

```C
typedef struct Vec_s {
    void *buffer;
    size_t elem_size;
    size_t buffer_size;
    size_t used;
} Vec_t;
```

Where:
- `buffer` is a pointer to the memory where the vector elements are stored.
- `elem_size` is the size of individual elements within the buffer (in bytes).
- `buffer_size` is the size of the buffer (in bytes).
- `used` is the number of elements occupied within the buffer.

You can declare a vector `vec` in the following way:

```C
Vec_t vec;
```

or

```C
struct Vec_s vec;
```

---

## Functions

### `vec_alloc`
Allocates a vector based on an initial buffer size.

```C
int vec_alloc(Vec_t *vec, size_t init_buff_size, size_t elem_size);
```

**Parameters**:
- `vec`: pointer to a vector.
- `init_buff_size`: initial allocation size of the buffer (in bytes).
- `elem_size`: size of buffer elements (in bytes).

**Returns**: 0 for success, -1 for failure.

**Usage Example:**
```C
Vec_t vec = {0};
vec_alloc(&vec, 20 * sizeof(int), sizeof(int));
```

### `vec_free`
Deallocates a vector.

```C
int vec_free(Vec_t *vec);
```

**Parameters**:
- `vec`: pointer to a vector.

**Returns**: 0 for success, -1 for failure.

**Usage Example:**
```C
vec_free(&vec);
```

### `vec_resize`
Increases or decreases the capacity of a vector.

```C
int vec_resize(Vec_t *vec, size_t new_buffer_size);
```

**Parameters**:
- `vec`: pointer to a vector.
- `new_buffer_size`: new allocation size of the vector's buffer (in bytes).

**Returns**: 0 for success, -1 for failure.

**Usage Example:**
```C
// the vec vector will now have 40 * size of an int bytes
vec_resize(&vec, 40 * sizeof(int));

// the vec vector will now have 20 * size of an int bytes
vec_resize(&vec, 20 * sizeof(int));
```

### `vec_reset`
Sets the number of used elements in a vector to 0, effectively resetting its elements.

```C
int vec_reset(Vec_t *vec);
```

**Parameters**:
- `vec`: pointer to a vector.

**Returns**: 0 for success, -1 for failure.

**Usage Example:**
```C
vec_reset(&vec);
```

### `vec_get`
Returns the memory address of a specific element in a vector.

```C
void *vec_get(Vec_t *vec, size_t index);
```

**Parameters**:
- `vec`: pointer to a vector.
- `index`: index of the desired element.

**Returns**: Address of the desired element.

**Usage Example:**
```C
void *addr = vec_get(&vec, 14);
```

### `vec_remove`
Removes an element from a vector at a specific index.

```C
int vec_remove(Vec_t *vec, size_t index);
```

**Parameters**:
- `vec`: pointer to a vector.
- `index`: index of the desired element.

**Returns**: 0 for success, -1 for failure.

**Usage Example:**
```C
// the element at index 5 will be removed from the vector
vec_remove(&vec, 5);
```

### `vec_push`
Pushes an element 'src' to the vector.

```C
int vec_push(Vec_t *vec, void *elem);
```

**Parameters**:
- `vec`: pointer to a vector.
- `elem`: source element src.

**Returns**: 0 for success, -1 for failure.

**Usage Example:**
```C
int value = 42;

// the value 42 will be stored at the top of the vec vector
vec_push(&vec, &value);
```

### `vec_pop`
Places the first element of a vector into 'dst'.

```C
int vec_pop(Vec_t *vec, void *dst);
```

**Parameters**:
- `vec`: pointer to a vector.
- `dst`: destination element.

**Returns**: 0 for success, -1 for failure.

**Usage Example:**
```C
int value;

// the first value present in the vec vector will be removed
// from this vector and stored in the 'value' variable
vec_pop(&vec, &value);
```

### `vec_insert`
Inserts an element into the vector at the index.

```C
int vec_insert(Vec_t *vec, void *elem, size_t index);
```

**Parameters**:
- `vec`: pointer to a vector.
- `elem`: source element src.
- `index`: index of the desired element.

**Returns**: 0 for success, -1 for failure.

**Usage Example:**
```C
int value = 99;

// the value 99 will be inserted at index 2 of vec
vec_insert(&vec, &value, 2);
```

### `vec_reverse`
Reorganizes the elements of a vector in reverse order (end to start).

```C
int vec_reverse(Vec_t *vec);
```

**Parameters**:
- `vec`: pointer to a vector.

**Returns**: 0 for success, -1 for failure.

**Usage Example:**
```C
// the elements of vec will be arranged in reverse order
vec_reverse(&vec);
```

### `vec_copy`
Copies the content of 'src' to 'dst'.

```C
int vec_copy(Vec_t *dst, Vec_t *src);
```

**Parameters**:
- `dst`: pointer to the destination vector.
- `src`: pointer to the source vector.

**Returns**: 0 for success, -1 for failure.

**Usage Example:**
```C
Vec_t new_vec = {0};

// new_vec will now contain all the elements belonging to vec
vec_copy(&new_vec, &vec);
```

### `vec_append`
Appends the content of 'src' to 'dst'.

```C
int vec_append(Vec_t *dst, Vec_t *src);
```

**Parameters**:
- `dst`: pointer to the destination vector.
- `src`: pointer to the source vector.

**Returns**: 0 for success, -1 for failure.

**Usage Example:**
```C
// the elements of new_vec will be post-appended to vec
vec_append(&vec, &new_vec);
```

### `vec_prepend`
Appends the content of 'src' to 'dst'.

```C
int vec_prepend(Vec_t *dst, Vec_t *src);
```

**Parameters**:
- `dst`: pointer to the destination vector.
- `src`: pointer to the source vector.

**Returns**: 0 for success, -1 for failure.

**Usage Example:**
```C
// the elements of new_vec

 will be pre-appended to vec
vec_prepend(&vec, &new_vec);
```

### `vec_compare`
Compares all elements of 2 vectors (they can have arbitrary sizes).

```C
int vec_compare(Vec_t *vec1, Vec_t *vec2);
```

**Parameters**:
- `vec1`: vector 1.
- `vec2`: vector 2.

**Returns**: 0 if all are equal, -1 if not.

**Usage Example:**
```C
int result = vec_compare(&vec, &new_vec);
```

### `vec_filter`
Filters the elements of src and stores them in dst based on a user-defined filter() function.

```C
int vec_filter(Vec_t *dst, Vec_t *src, bool (*filter)(void*));
```

**Parameters**:
- `dst`: pointer to the destination vector.
- `src`: pointer to the source vector.
- `filter`: pointer to a filter function.

**Returns**: 0 if successful, -1 if failed.

**Usage Example:**
```C
// definition of the filtering function
static bool is_even(void *element) {
    return (*(int *) element % 2 == 0);
}

// only the even integer elements will be stored in new_vec
vec_filter(&new_vec, &vec, is_even);
```

### `vec_iter`
Iterates over the elements of a vector and calls a user-defined function (iter()) for each iterated element.

```C
int vec_iter(Vec_t *vec, void (*iter)(void *));
```

**Parameters**:
- `vec`: pointer to a vector.

**Returns**: 0 if successful, -1 if failed.

**Usage Example:**
```C
// definition of an iterating function
static void sum_int(void *element) {
    *(int *) element += 1;
}

// this will increment each element of the vector
vec_iter(&vec, sum_int);
```
