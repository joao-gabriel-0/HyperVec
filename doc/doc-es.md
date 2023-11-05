# Documentación

Este archivo contiene información básica sobre cada una de las funcionalidades proporcionadas por HyperVec.

## Definición básica del vector

``` C
typedef struct Vec_s {
    void *buffer;
    size_t elem_size;
    size_t buffer_size;
    size_t used;
} Vec_t;
```

Donde:
- "buffer" es un puntero a la memoria donde se almacenan los elementos del vector.
- "elem_size" es el tamaño (en bytes) de los elementos individuales dentro del búfer.
- "buffer_size" es el tamaño (en bytes) del vector.
- "used" es el número de elementos ya ocupados dentro del búfer (es decir, ocupados).

## Funciones

"vec_alloc" es el inicializador de todo el vector, aloja un vector en la memoria en función de un tamaño inicial de búfer.
``` C
int vec_alloc(Vec_t *vec, size_t init_buff_size, size_t elem_size);
```

**Parámetros**:
- "vec" puntero a un vector.
- "init_buff_size" tamaño inicial (en bytes) para la asignación del vector.
- "elem_size" tamaño (en bytes) de los elementos individuales del vector.

**Retorno**:
0 para éxito, -1 si hay algún error.
