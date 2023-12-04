# Hypervec

Uma Biblioteca Pública de Código Aberto para Lidar com Operações Dinâmicas de Vetores em C com Segurança

---

## Como ler esta documentação?

### Tipos de Vetores

Esta documentação está dividida em 2 partes, **Vetores Genéricos** e **Vetores Numéricos**.

Os Vetores Genéricos representam arrays dinâmicos unidimensionais projetados para acomodar uma sequência de endereços arbitrários (`void*`). Esses vetores são especificamente elaborados para cenários que exigem o armazenamento e manipulação de diversos tipos de dados dentro de uma estrutura linear de comprimento indefinido.

Os Vetores Numéricos, por outro lado, são arrays unidimensionais projetados para armazenar uma sequência de números `double`. Desprovidos de um comprimento predefinido, esses vetores são projetados para suportar operações matemáticas, tais como: normalização, ordenação, produto escalar, convolução, etc.

### Indicadores de Estado de Recursos

Os Indicadores de Estado de Recursos (FSI) são representados por caixas coloridas para comunicar o status de um recurso, categorizando-o como _em breve_, _experimental_, _instável_ ou _descontinuado_:

- **<span style="border-radius:5px; padding:2px; background-color:rgb(255, 165, 0); color:rgb(240, 240, 240)">Em Breve</span>**: Este indicador significa que um recurso está atualmente em desenvolvimento e será lançado em um futuro próximo.

- **<span style="border-radius:5px; padding:2px; background-color:rgb(52, 152, 219); color:rgb(240, 240, 240)">Experimental</span>**: Esta designação indica que um recurso específico está em uma fase experimental, e sua inclusão como um recurso oficial em lançamentos futuros está sujeita a uma avaliação adicional.

- **<span style="border-radius:5px; padding:2px; background-color:rgb(181, 197, 38); color:rgb(240, 240, 240)">Instável</span>**: Recursos rotulados como "Instáveis" ainda não são considerados adequados para ambientes de produção, apresentando potenciais riscos para os usuários finais.

- **<span style="border-radius:5px; padding:2px; background-color:rgb(220, 20, 60); color:rgb(240, 240, 240)">Descontinuado</span>**: O status "Descontinuado" indica que um recurso específico não é mais suportado ou foi removido da biblioteca.

Recursos que não estão marcados com um FSI já são suportados pela biblioteca.

---

## Vetores Genéricos

### Estrutura Básica de Vetor Genérico

Cada Vetor Genérico é composto por uma estrutura básica:

```c
typedef struct GVec_s {
    void *buffer;
    size_t allocation_size;
    size_t elem_size;
    size_t capacity; 
    size_t occupied;
} GVec_t;
```

Onde:

- `void *buffer` é um ponteiro para o buffer de memória alocado.

- `size_t allocation_size` é o tamanho total do buffer de memória alocado.

- `size_t elem_size` é o tamanho de cada elemento individual no buffer.

- `size_t capacity` é o número máximo de elementos suportados pelo buffer (dado por allocation_size / elem_size).

- `size_t occupied` é o número de elementos atualmente ocupados no buffer.

### Funções de Manipulação de Vetores Genéricos

#### gv_alloc()

Aloca um Vetor Genérico `v` com uma capacidade inicial `capacity` de um tipo definido `type`.

```c
#define gv_alloc(v, capacity, type) \
    __gv_alloc(&v, (capacity), sizeof(type))
```

#### __gv_alloc()

Aloca um Vetor Genérico `v` com uma capacidade inicial `capacity` que contém vários elementos de um tamanho `elem_size` definido.

```c
int __gv_alloc(GVec_t *v, size_t capacity, size_t elem_size);
```

#### gv_free()

Desaloca um Vetor Genérico `v`.

```c
#define gv_free(v) \
    __gv_free(&v)

int __gv_free(GVec_t *v);
```

#### gv_extend()

Estende um Vetor Genérico `v`, alterando sua capacidade para uma nova capacidade: `new_capacity`.

```c
#define gv_extend(v, new_capacity) \
    __gv_extend(&v, new_capacity)

int __gv_extend(GVec_t *v, size_t new_capacity);
```

#### gv_shrink() **<span style="border-radius:5px; padding:2px; background-color:rgb(255, 165, 0); color:rgb(240, 240, 240)">Em Breve</span>**

```c
#define gv_shrink(v, new_capacity) \
    __gv_shrink(&v, new_capacity)

int __gv_shrink(GVec_t *v, size_t new_capacity);
```

#### gv_get()

Retorna o endereço de memória um elemento em um índice (`elem_index`) de um Vetor Genérico `v`.

```c
#define gv_get(v, elem_index) \
    __gv_get(&v, elem_index)

void *__gv_get(GVec_t *v, size_t elem_index);
```

#### gv_push()

Empurra o endereço de um elemento (`elem`) para um Vetor Genérico `v`, estendendo-o se necessário.
Quando o vetor é extendido, este é feito com base em uma constante:

```c
#define __GV_PUSH_REEXTEND_RATE 2
```

$$
\texttt{new capacity} = \texttt{PUSH REEXTEND RATE} \cdot n
$$

```c
#define gv_push(v, elem) \
    __gv_push(&v, &elem)

int __gv_push(GVec_t *v, void *elem_addr);
```

#### gv_pop() **<span style="border-radius:5px; padding:2px; background-color:rgb(181, 197, 38); color:rgb(240, 240, 240)">Instável</span>**

Efetua um pop no endereço do elemento superior de um Vetor Genérico `v` para um ponteiro `dst`.

NOTA: a operação Pop ainda não reduz o vetor após ser realizada, portanto, está marcada como **<span style="border-radius:5px; padding:2px; background-color:rgb(181, 197, 38); color:rgb(240, 240, 240)">Instável</span>**.

```c
#define gv_pop(v, dst

) \
    __gv_pop(&v, &dst)

int __gv_pop(GVec_t *v, void *dst_addr);
```

#### gv_insert() **<span style="border-radius:5px; padding:2px; background-color:rgb(255, 165, 0); color:rgb(240, 240, 240)">Em Breve</span>**

```c
#define gv_insert(v, elem) \
    __gv_insert(&v, &elem);

int __gv_insert(GVec_t *v, void* elem);
```

#### gv_remove() **<span style="border-radius:5px; padding:2px; background-color:rgb(255, 165, 0); color:rgb(240, 240, 240)">Em Breve</span>**

```c
#define gv_remove(v, dst) \
    __gv_insert(&v, &dst);

int __gv_remove(GVec_t *v, void* dst);
```

#### gv_iter()

Itera por todos os elementos de um Vetor Genérico `v` usando uma função definida pelo usuário `f`.

```c
#define gv_iter(v, f) \
    __gv_iter(&v, f)

int __gv_iter(GVec_t *v, void (*f)(void*));
```

---

## Vetores Numéricos

### Estrutura Básica de Vetor Numérico

```c
typedef struct NVec_s {
    double *buffer;
    size_t allocation_size;
    size_t elem_size;
    size_t capacity; 
    size_t occupied;
} NVec_t;
```

### Funções de Manipulação de Vetor Numérico
