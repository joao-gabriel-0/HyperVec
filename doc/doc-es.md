# Hipervec

Una biblioteca pública de código abierto para manejar operaciones vectoriales dinámicas en C de forma segura

---

## ¿Cómo leer esta documentación?

### Tipos de Vectores

Esta documentación se divide en 2 partes, **Vectores Genéricos** y **Vectores Numéricos**.

Los Vectores Genéricos representan matrices unidimensionales diseñadas para acomodar una secuencia de direcciones arbitrarias (`void*`). Estos vectores están específicamente diseñados para escenarios que requieren el almacenamiento y manipulación de diversos tipos de datos dentro de una estructura lineal de longitud indefinida.

Por otro lado, los Vectores Numéricos son matrices unidimensionales diseñadas para contener una secuencia de números tipo double. Sin una longitud predefinida, estos vectores están diseñados para admitir operaciones matemáticas como normalización, ordenamiento, producto punto, convolución, etc.

### Indicadores de Estado de Funciones

Los Indicadores de Estado de Funciones (FSI) están representados por cuadros con colores para comunicar el estado de una función, clasificándola como _próximamente_, _experimental_, _inestable_ o _en desuso_:

- **<span style="border-radius:5px; padding:2px; background-color:rgb(255, 165, 0); color:rgb(240, 240, 240)">Próximamente</span>**: Este indicador significa que una función está actualmente en desarrollo y se lanzará en el futuro cercano.

- **<span style="border-radius:5px; padding:2px; background-color:rgb(52, 152, 219); color:rgb(240, 240, 240)">Experimental</span>**: Esta designación indica que una característica específica se encuentra en una fase experimental y su inclusión como característica oficial en versiones futuras está sujeta a evaluación adicional.

- **<span style="border-radius:5px; padding:2px; background-color:rgb(181, 197, 38); color:rgb(240, 240, 240)">Inestable</span>**: Las funciones etiquetadas como "Inestables" aún no se consideran adecuadas para entornos de producción, lo que plantea riesgos potenciales para los usuarios finales.

- **<span style="border-radius:5px; padding:2px; background-color:rgb(220, 20, 60); color:rgb(240, 240, 240)">En Desuso</span>**: El estado "En Desuso" indica que una característica específica ya no es compatible y se ha eliminado de la biblioteca.

Las funciones que no están marcadas con un FSI ya son compatibles con la biblioteca.

---

## Vectores Genéricos

### Estructura Básica del Vector Genérico

Cada Vector Genérico está compuesto por una estructura básica:

```c
typedef struct GVec_s {
    void *buffer;
    size_t allocation_size;
    size_t elem_size;
    size_t capacity; 
    size_t occupied;
} GVec_t;
```

Donde:

- `void *buffer` es un puntero al búfer de memoria asignado.

- `size_t allocation_size` es el tamaño total del búfer de memoria asignado.

- `size_t elem_size` es el tamaño de cada elemento individual en el búfer.

- `size_t capacity` es el número máximo de elementos admitidos por el búfer (dado por allocation_size / elem_size).

- `size_t occupied` es el número de elementos actualmente ocupados en el búfer.

### Funciones de Manipulación del Vector Genérico

#### `gv_alloc()`

Asigna un Vector Genérico `v` con una capacidad inicial de un tipo definido.

```c
#define gv_alloc(v, capacity, type) \
    __gv_alloc(&v, (capacity), sizeof(type))
```

#### `__gv_alloc()`

Asigna un Vector Genérico `v` con una capacidad inicial que contiene múltiples elementos de un tamaño definido `elem_size`.

```c
int __gv_alloc(GVec_t *v, size_t capacity, size_t elem_size);
```

#### `gv_free()`

Desasigna un Vector Genérico `v`.

```c
#define gv_free(v) \
    __gv_free(&v)

int __gv_free(GVec_t *v);
```

#### `gv_extend()`

Extiende un Vector Genérico `v`, cambiando su capacidad a una `new_capacity`.

```c
#define gv_extend(v, new_capacity) \
    __gv_extend(&v, new_capacity)

int __gv_extend(GVec_t *v, size_t new_capacity);
```

#### `gv_shrink()` **<span style="border-radius:5px; padding:2px; background-color:rgb(255, 165, 0); color:rgb(240, 240, 240)">Próximamente</span>**

```c
#define gv_shrink(v, new_capacity) \
    __gv_shrink(&v, new_capacity)

int __gv_shrink(GVec_t *v, size_t new_capacity);
```

#### `gv_get()`

Devuelve la dirección de un elemento en un índice (`elem_index`) de un Vector Genérico `v`.

```c
#define gv_get(v, elem_index) \
    __gv_get(&v, elem_index)

void *__gv_get(GVec_t *v, size_t elem_index);
```

#### `gv_push()`

Inserta la dirección de un elemento (`elem`) en un Vector Genérico `v`, extendiéndolo si es necesario.

Cuando el vector se extiende, lo hace basándose en una constante:

```c
#define __GV_PUSH_REEXTEND_RATE 2
```

```c
#define gv_push(v, elem) \
    __gv_push(&v, &elem)

int __gv_push(GVec_t *v, void *elem_addr);
```

#### `gv_pop()` **<span style="border-radius:5px; padding:2px; background-color:rgb(181, 197, 38); color:rgb(240, 240, 240)">Inestable</span>**

Extrae la dirección del elemento superior de un Vector Genérico `v` a un puntero `dst`.

NOTA: la operación pop aún no reduce el tamaño del vector después de realizarse, por lo tanto, se marca como **<span style="border-radius:5px; padding:2px; background-color:rgb(181, 197, 38); color:rgb(240, 240, 240)">Inestable</span>**.

```c
#define gv_pop(v, dst) \
    __gv_pop(&v, &dst)

int __gv_pop(GVec_t *v, void *dst_addr);
```

#### `gv_insert()` **<span style="border-radius:

5px; padding:2px; background-color:rgb(255, 165, 0); color:rgb(240, 240, 240)">Próximamente</span>**

```c
#define gv_insert(v, elem) \
    __gv_insert(&v, &elem);

int __gv_insert(GVec_t *v, void* elem);
```

#### `gv_remove()` **<span style="border-radius:5px; padding:2px; background-color:rgb(255, 165, 0); color:rgb(240, 240, 240)">Próximamente</span>**

```c
#define gv_remove(v, dst) \
    __gv_insert(&v, &dst);

int __gv_remove(GVec_t *v, void* dst);
```

#### `gv_iter()`

Itera a través de cada elemento de un Vector Genérico `v` usando una función definida por el usuario `f`.

```c
#define gv_iter(v, f) \
    __gv_iter(&v, f)

int __gv_iter(GVec_t *v, void (*f)(void*));
```

---

## Vectores Numéricos

### Estructura Básica del Vector Numérico

```c
typedef struct NVec_s {
    double *buffer;
    size_t allocation_size;
    size_t elem_size;
    size_t capacity; 
    size_t occupied;
} NVec_t;
```

### Funciones de Manipulación del Vector Numérico
