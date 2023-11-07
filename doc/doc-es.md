# Documentación de HyperVec

Este archivo contiene información básica sobre lo que hace cada una de las funcionalidades proporcionadas por HyperVec.

---

## Definición de la estructura de vector

El bloque de construcción básico de HyperVec es el tipo de datos ```Vec_t```, definido de la siguiente manera:

``` C
typedef struct Vec_s {
    void *buffer;
    size_t elem_size;
    size_t buffer_size;
    size_t used;
} Vec_t;
```

Donde:
- ``buffer`` es un puntero a la memoria donde se almacenan los elementos del vector.
- ``elem_size`` es el tamaño de los elementos individuales dentro del búfer (en bytes).
- ``buffer_size`` es el tamaño del búfer (en bytes).
- ``used`` es el número de elementos ocupados dentro del búfer.

Aquí, puedes elegir entre declarar un vector ```vec``` de la siguiente manera:

``` C
Vec_t vec;
```

o

``` C
struct Vec_s vec;
```

---

## Funciones

``vec_alloc`` asigna un vector basado en un tamaño de búfer inicial.
``` C
int vec_alloc(Vec_t *vec, size_t init_buff_size, size_t elem_size);
```
**Parámetros**:
- ``vec`` es un puntero a un vector.
- ``init_buff_size`` es el tamaño de asignación inicial del búfer (en bytes).
- ``elem_size`` es el tamaño de los elementos individuales del búfer (en bytes).

**Retorno**:
0 para éxito, -1 para fallo.

**Ejemplo:**

Supongamos que deseas asignar un vector que inicialmente puede contener 20 números enteros:
```C
// primero declaramos un vector
Vec_t vec1 = {0};

// luego podemos asignarlo según el tamaño deseado
vec_alloc(&vec1, 20 * sizeof(int), sizeof(int));
```