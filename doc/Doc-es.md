Hipervec
Una biblioteca pública de código abierto para manejar operaciones vectoriales dinámicas en C de forma segura
 
¿Cómo leer esta documentación?
Tipos de vectores
Esta documentación se divide en 2 partes, Vectores genéricos y Vectores numéricos.
- Los vectores genéricos representan matrices de sonido unidimensionales diseñadas para acomodar una secuencia de preguntas arbitrarias (void*). Estos vectores son específicos de configuraciones que bloquean el almacenamiento y manipulación de diferentes tipos de datos dentro de una estructura lineal de longitud indefinida.  
- Los vectores numéricos, por otro lado, son matrices unidimensionales diseñadas para almacenar una secuencia de números double. Al carecer de una longitud predefinida, estos vectores son específicos para soportar operaciones matemáticas, como: normalización, ordenamiento, producto escalar, convolución, etc.
Indicadores de estado de recursos
Los indicadores de estado de funciones (FSI) están representados por cuadros de colores para comunicar el estado de una función, categorizándola como próximamente, experimental, aterradora o descontinuada:
 
• Próximamente: este indicador significa que una función está actualmente en desarrollo y se lanzará en un futuro próximo.
 
• Experimental: esta designación indica que una característica específica se encuentra en una fase experimental y su inclusión como característica oficial en versiones futuras está sujeta a evaluación
adicional.
 
• Inestable: las funciones etiquetadas como "inestables" aún no se consideran adecuadas para entornos de producción, lo que plantea riesgos potenciales para los usuarios finales.
• En desuso: el estado "En desuso" indica que una característica específica ya no es compatible o se ha eliminado de la biblioteca.
 
La biblioteca ya admite funciones que no están marcadas con un FSI.
 
 
Genéricos
 
Estructura vectorial genérica básica
 
Cada Vector Genérico se compone de una estructura básica:
 
typedef struct GVec_s {
void *buffer;
size_t allocation_size;
size_t elem_size;  
size_t capacity;
size_t occupied;
} GVec_t;
 
 
Dónde:
 
 
• void *buffer es un puntero al búfer de memoria asignado.
 
• size_allocation_size es el tamaño total del búfer de memoria asignado.
 
• size_t elem_size es el tamaño de cada elemento individual en el búfer.
 
• size_t capacity es el número máximo de elementos admitidos por el búfer (dado por asignación_tamaño / elem_size).
 
• size_t occupied es el número de elementos actualmente ocupados en el búfer.
 
Funciones genéricas de manipulación de vectores:
 
gv_alloc()
 
Asigna un vector genérico v con una capacity inicial de un tipo definido.
#define gv_alloc(v, capacity, type) \
   __gv_alloc(&v, (capacity), sizeof(type))
 
__gv_alloc()
 
Asigna un Vector genérico v con una capacity inicial que contiene múltiples elementos de un tamaño definido elem_size.
 
int __gv_alloc(GVec_t *v, size_t capacity, size_t elem_size);
 
gv_free()
 
Desasigna un vector genérico v
 
#define gv_free(v) \
   __gv_free(&v)
 
int __gv_free(GVec_t *v);
 
gv_extend()
 
Extiende un Vector genérico v, cambiando su capacidad a una nueva capacidad: new_capacity.
 
#define gv_extend(v, new_capacity) \
   __gv_extend(&v, new_capacity)
 
int __gv_extend(GVec_t *v, size_t new_capacity);
 
 
 
gv_get()
 
Devuelve la dirección de memoria de un elemento en un índice (elem_index) de un vector genérico v
 
#define gv_get(v, elem_index) \
   __gv_get(&v, elem_index)
 
void *__gv_get(GVec_t *v, size_t elem_index);
 
gv_push()
 
Inserta la dirección de un elemento ( elem ) en un vector genérico v, extendiéndolo si es necesario. Cuando se extiende el vector, se hace en base a una constante:
 
#define __GV_PUSH_REEXTEND_RATE 2
 

 
 
#define gv_push(v, elem) \
   __gv_push(&v, &elem)
 
int __gv_push(GVec_t *v, void *elem_addr);
 
 
 
gv_pop() Instável
 
Muestra la dirección del elemento superior de un vector genérico en un puntero dst.
 
NOTA: la operación Pop aún no reduce el vector después de realizarse, por lo tanto, se marca como Inestable.
 
#define gv_pop(v, dst
) \
   __gv_pop(&v, &dst)
int __gv_pop(GVec_t *v, void *dst_addr);
 
gv_insert() Breve
 
#define gv_insert(v, elem) \
   __gv_insert(&v, &elem);
 
int __gv_insert(GVec_t *v, void* elem);
 
gv_remove() Breve
 
#define gv_remove(v, dst) \
   __gv_insert(&v, &dst);
 
int __gv_remove(GVec_t *v, void* dst);
 
 
gv_iter()
 
Itera a través de todos los elementos de un vector genérico utilizando una función definida por el usuario f.
 
#define gv_iter(v, f) \
   __gv_iter(&v, f)
 
int __gv_iter(GVec_t *v, void (*f)(void*));
 
Vectores numéricos
 
Estructura vectorial numérica básica
 
typedef struct NVec_s {
   double *buffer;
   size_t allocation_size;
   size_t elem_size;
   size_t capacity;
   size_t occupied;
} NVec_t;
 
