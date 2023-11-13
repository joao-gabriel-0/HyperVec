# Documentação da HyperVec

Este arquivo contém informações básicas sobre o que cada uma das funcionalidades fornecidas pela HyperVec faz.

---

## Definição da estrutura de vetor

O bloco de construção básico da HyperVec é o tipo de dado ```Vec_t```, definido da seguinte forma:

``` C
typedef struct Vec_s {
    void *buffer;
    size_t elem_size;
    size_t buffer_size;
    size_t used;
} Vec_t;
```

Onde:
- ``buffer`` é um ponteiro para a memória onde os elementos do vetor são armazenados.
- ``elem_size`` é o tamanho dos elementos individuais dentro do buffer (em bytes).
- ``buffer_size`` é o tamanho do buffer (em bytes).
- ``used`` é o número de elementos ocupados dentro do buffer.

Aqui, você pode escolher entre declarar um vetor ```vec``` da seguinte forma:

``` C
Vec_t vec;
```

ou

``` C
struct Vec_s vec;
```

---

## Funções

``vec_alloc`` aloca um vetor com base em um tamanho de buffer inicial.
``` C
int vec_alloc(Vec_t *vec, size_t init_buff_size, size_t elem_size);
```
**Parâmetros**:
- ``vec`` é um ponteiro para um vetor.
- ``init_buff_size`` é o tamanho de alocação inicial do buffer (em bytes).
- ``elem_size`` é o tamanho dos elementos do buffer (em bytes).

**Retorno**:
0 para sucesso, -1 para falha.

**Exemplo:**

Digamos que você deseja alocar um vetor que pode inicialmente conter 20 números inteiros:
```C
// primeiro declaramos um vetor
Vec_t vec1 = {0};

// então podemos alocá-lo com base no tamanho desejado
vec_alloc(&vec1, 20 * sizeof(int), sizeof(int));
```

`` vec_free`` desaloca um vetor.
``` C
int vec_free(Vec_t *vec);
```
**Parâmetros**:
- ``vec`` é um ponteiro para um vetor.
  
**Retorno**:
0 para sucesso, -1 para falha.


`` vec_resize`` reescreve o tamanho de um vetor.
``` C
int vec_resize(Vec_t *vec, size_t new_buffer_size);
```
**Parâmetros**:
- ``vec`` é um ponteiro para um vetor.
- `` new_buffer_size `` novo tamanho de alocação de buffer (em bytes).

**Retorno**:
0 para sucesso, -1 para falha.

``vec_reset`` define a variável 'usada' de um vetor como 0, redefinindo-a efetivamente.
``` C
int vec_reset(Vec_t *vec);
```
**Parâmetros**:
- ``vec`` é um ponteiro para um vetor.

**Retorno**:
0 para sucesso, -1 para falha.

``vec_get`` recupera o endereço de um elemento de um vetor com base em um índice específico.
``` C
void *vec_get(Vec_t *vec, size_t index);
```
**Parâmetros**:
- ``vec`` é um ponteiro para um vetor.
- `` index `` índice do elemento desejado.
 
**Retorno**:
endereço do elemento desejado.

``vec_remove`` remove um elemento de um vetor em um índice específico.
``` C
int vec_remove(Vec_t *vec, size_t index);
```
**Parâmetros**:
- ``vec`` é um ponteiro para um vetor.
- ``index`` índice do elemento desejado.
 
**Retorno**:
0 para sucesso, -1 para falha.

``vec_push`` empurra um elemento 'src' para o vetor.
``` C
int vec_push(Vec_t *vec, void *elem);
```
**Parâmetros**:
- ``vec`` é um ponteiro para um vetor.
- ``elem`` elemento de origem src.
 
**Retorno**:
0 para sucesso, -1 para falha.

``vec_pop`` coloca o primeiro elemento de um vetor em 'dst'.
``` C
int vec_pop(Vec_t *vec, void *dst);
```
**Parâmetros**:
- ``vec`` é um ponteiro para um vetor.
- ``dst`` elemento de destino.
 
**Retorno**:
0 para sucesso, -1 para falha.

``vec_insert`` insere um elemento no vetor no índice.
``` C
int vec_insert(Vec_t *vec, void *elem, size_t index);
```
**Parâmetros**:
- ``vec`` é um ponteiro para um vetor.
- ``elem`` elemento de origem src.
- ``index`` índice do elemento desejado.
 
**Retorno**:
0 para sucesso, -1 para falha.

``vec_revert`` reorganiza os elementos de um vetor na ordem inversa (fim para início).
``` C
int vec_revert(Vec_t *vec);
```
**Parâmetros**:
- ``vec`` é um ponteiro para um vetor.

**Retorno**:
0 para sucesso, -1 para falha.

``vec_copy`` copia o conteúdo de 'src' para 'dst'.
``` C
int vec_copy(Vec_t *dst, Vec_t *src);
```
**Parâmetros**:
- ``dst`` ponteiro para o vetor de destino.
- ``src`` ponteiro para o vetor de origem.
 
**Retorno**:
0 para sucesso, -1 para falha.

``vec_append`` anexa o conteúdo de 'src' a 'dst'.
``` C
int vec_append(Vec_t *dst, Vec_t *src);
```
**Parâmetros**:
- ``dst`` ponteiro para o vetor de destino.
- ``src`` ponteiro para o vetor de origem.
 
**Retorno**:
0 para sucesso, -1 para falha.

``vec_prepend`` acrescenta o conteúdo de 'src' a 'dst'.
``` C
int vec_prepend(Vec_t *dst, Vec_t *src);
```
**Parâmetros**:
- ``dst`` ponteiro para o vetor de destino.
- ``src`` ponteiro para o vetor de origem.
 
**Retorno**:
0 para sucesso, -1 para falha.


``vec_compare`` compara todos os elementos de 2 vetores (eles podem ter tamanhos arbitrários).
``` C
int vec_compare(Vec_t *vec1, Vec_t *vec2);
```
**Parâmetros**:
- ``vec1`` vetor 1.
- ``vec2`` vetor 2.
 
**Retorno**:
0 se forem todos iguais, -1 se não.

``vec_filter`` filtra os elementos de src e os armazena em dst com base em uma função filter() definida pelo usuário .
``` C
int vec_filter(Vec_t *dst, Vec_t *src, bool (*filter)(void*));
```
**Parâmetros**:
- ``dst`` ponteiro para o vetor de destino.
- ``src`` ponteiro para o vetor de origem.
- ``filter`` ponteiro para uma função de filtro.
 
**Retorno**:
0 se forem todos iguais, -1 se não.

``vec_iter`` itera os elementos de um vetor e chama uma função definida pelo usuário iter() para cada elemento.
``` C
int vec_iter(Vec_t *vec, void (*iter) (void *));
```
**Parâmetros**:
- ``vec`` é um ponteiro para um vetor.
 
**Retorno**:
0 se forem todos iguais, -1 se não.




