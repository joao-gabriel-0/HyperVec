# Documentación de HyperVec

Este archivo proporciona información sobre las funcionalidades de HyperVec, presentadas en el orden en que están definidas en el archivo "Hypervec.h".

---

## Definición de la estructura del vector

El elemento fundamental de HyperVec es el tipo de dato `Vec_t`, definido de la siguiente manera en "Hypervec.h":

``` C
typedef struct Vec_s {
    void *buffer;
    size_t elem_size;
    size_t buffer_size;
    size_t used;
} Vec_t;
```

Donde:
- `buffer` es un puntero a la memoria donde se almacenan los elementos del vector.
- `elem_size` es el tamaño de los elementos individuales dentro del búfer (en bytes).
- `buffer_size` es el tamaño del búfer (en bytes).
- `used` es el número de elementos ocupados dentro del búfer.

Puede declarar un vector `vec` de la siguiente manera:

``` C
Vec_t vec;
```

o

``` C
struct Vec_s vec;
```

---

## Funciones

### `vec_alloc`
Asigna dinámicamente un vector basado en un tamaño de búfer inicial.

``` C
int vec_alloc(Vec_t *vec, size_t init_buff_size, size_t elem_size);
```

**Parámetros**:
- `vec`: puntero a un vector.
- `init_buff_size`: tamaño inicial de asignación del búfer (en bytes).
- `elem_size`: tamaño de los elementos del búfer (en bytes).

**Devuelve**: 0 para éxito, -1 para falla.

**Ejemplo de uso:**
```C
Vec_t vec = {0};
vec_alloc(&vec, 20 * sizeof(int), sizeof(int));
```

### `vec_free`
Libera la memoria asignada para un vector.

``` C
int vec_free(Vec_t *vec);
```

**Parámetros**:
- `vec`: puntero a un vector.

**Devuelve**: 0 para éxito, -1 para falla.

**Ejemplo de uso:**
```C
vec_free(&vec);
```

### `vec_resize`
Aumenta o disminuye la capacidad de un vector.

``` C
int vec_resize(Vec_t *vec, size_t new_buffer_size);
```

**Parámetros**:
- `vec`: puntero a un vector.
- `new_buffer_size`: nuevo tamaño de asignación del búfer del vector (en bytes).

**Devuelve**: 0 para éxito, -1 para falla.

**Ejemplo de uso:**
```C
// el vector vec tendrá ahora 40 * tamaño de un int bytes
vec_resize(&vec, 40 * sizeof(int));

// el vector vec tendrá ahora 20 * tamaño de un int bytes
vec_resize(&vec, 20 * sizeof(int));
```

### `vec_reset`
Establece el número de elementos utilizados en un vector como 0, restableciendo efectivamente sus elementos.

``` C
int vec_reset(Vec_t *vec);
```

**Parámetros**:
- `vec`: puntero a un vector.

**Devuelve**: 0 para éxito, -1 para falla.

**Ejemplo de uso:**
```C
vec_reset(&vec);
```

### `vec_get`
Devuelve la dirección de memoria de un elemento específico de un vector.

``` C
void *vec_get(Vec_t *vec, size_t index);
```

**Parámetros**:
- `vec`: puntero a un vector.
- `index`: índice del elemento deseado.

**Devuelve**: Dirección del elemento deseado.

**Ejemplo de uso:**
```C
void *addr = vec_get(&vec, 14);
```

### `vec_remove`
Elimina un elemento de un vector en un índice específico.

``` C
int vec_remove(Vec_t *vec, size_t index);
```

**Parámetros**:
- `vec`: puntero a un vector.
- `index`: índice del elemento deseado.

**Devuelve**: 0 para éxito, -1 para falla.

**Ejemplo de uso:**
```C
// el elemento en el índice 5 se eliminará del vector
vec_remove(&vec, 5);
```

### `vec_push`
Añade un elemento 'src' al vector.

``` C
int vec_push(Vec_t *vec, void *elem);
```

**Parámetros**:
- `vec`: puntero a un vector.
- `elem`: elemento origen src.

**Devuelve**: 0 para éxito, -1 para falla.

**Ejemplo de uso:**
```C
int value = 42;

// el valor 42 se almacenará en la parte superior del vector vec
vec_push(&vec, &value);
```

### `vec_pop`
Coloca el primer elemento de un vector en 'dst'.

``` C
int vec_pop(Vec_t *vec, void *dst);
```

**Parámetros**:
- `vec`: puntero a un vector.
- `dst`: elemento de destino.

**Devuelve**: 0 para éxito, -1 para falla.

**Ejemplo de uso:**
```C
int value;

// el primer valor presente en el vector vec se eliminará 
// de este vector y se almacenará en la variable 'value'
vec_pop(&vec, &value);
```

### `vec_insert`
Inserta un elemento en el vector en el índice.

``` C
int vec_insert(Vec_t *vec, void *elem, size_t index);
```

**Parámetros**:
- `vec`: puntero a un vector.
- `elem`: elemento origen src.
- `index`: índice del elemento deseado.

**Devuelve**: 0 para éxito, -1 para falla.

**Ejemplo de uso:**
```C
int value = 99;

// el valor 99 se insertará en el índice 2 de vec
vec_insert(&vec, &value, 2);
```

### `vec_reverse`
Reorganiza los elementos de un vector en orden inverso (fin a inicio).

``` C
int vec_reverse(Vec_t *vec);
```

**Parámetros**:
- `vec`: puntero a un vector.

**Devuelve**: 0 para éxito, -1 para falla.

**Ejemplo de uso:**
```C
// los elementos de vec se organizarán en orden inverso
vec_reverse(&vec);
```

### `vec_copy`
Copia el contenido de 'src' a 'dst'.

``` C
int vec_copy(Vec_t *dst, Vec_t *src);
```

**Parámetros**:
- `dst`: puntero al vector de destino.
- `src`: puntero al vector de origen.

**Devuelve**: 0 para éxito, -1 para falla.

**Ejemplo de uso:**
```C
Vec_t new_vec = {0};

// new_vec contendrá todos los elementos pertenecientes a vec
vec_copy(&new_vec, &vec);
```

### `vec_append`
Adjunta el contenido de '

src' a 'dst'.

``` C
int vec_append(Vec_t *dst, Vec_t *src);
```

**Parámetros**:
- `dst`: puntero al vector de destino.
- `src`: puntero al vector de origen.

**Devuelve**: 0 para éxito, -1 para falla.

**Ejemplo de uso:**
```C
// los elementos de new_vec se adjuntarán después en vec
vec_append(&vec, &new_vec);
```

### `vec_prepend`
Añade el contenido de 'src' a 'dst'.

``` C
int vec_prepend(Vec_t *dst, Vec_t *src);
```

**Parámetros**:
- `dst`: puntero al vector de destino.
- `src`: puntero al vector de origen.

**Devuelve**: 0 para éxito, -1 para falla.

**Ejemplo de uso:**
```C
// los elementos de new_vec se adjuntarán antes en vec
vec_prepend(&vec, &new_vec);
```

### `vec_compare`
Compara todos los elementos de 2 vectores (pueden tener tamaños arbitrarios).

``` C
int vec_compare(Vec_t *vec1, Vec_t *vec2);
```

**Parámetros**:
- `vec1`: vector 1.
- `vec2`: vector 2.

**Devuelve**: 0 si son todos iguales, -1 si no.

**Ejemplo de uso:**
```C
int result = vec_compare(&vec, &new_vec);
```

### `vec_filter`
Filtra los elementos de src y los almacena en dst según una función filter() definida por el usuario.

``` C
int vec_filter(Vec_t *dst, Vec_t *src, bool (*filter)(void*));
```

**Parámetros**:
- `dst`: puntero al vector de destino.
- `src`: puntero al vector de origen.
- `filter`: puntero a una función de filtro.

**Devuelve**: 0 si tiene éxito, -1 si falla.

**Ejemplo de uso:**
```C
// definición de la función de filtrado
static bool is_even(void *element) {
    return (*(int *) element % 2 == 0);
}

// solo se almacenarán los elementos enteros pares en new_vec
vec_filter(&new_vec, &vec, is_even);
```

### `vec_iter`
Itera sobre los elementos de un vector y llama a una función definida por el usuario (iter()) para cada elemento iterado.

``` C
int vec_iter(Vec_t *vec, void (*iter)(void *));
```

**Parámetros**:
- `vec`: puntero a un vector.

**Devuelve**: 0 si tiene éxito, -1 si falla.

**Ejemplo de uso:**
```C
// definición de una función iteradora
static void sum_int(void *element) {
    *(int *) element += 1;
}

// esto incrementará cada elemento del vector
vec_iter(&vec, sum_int);
```
