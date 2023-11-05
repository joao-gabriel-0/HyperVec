# Documentação

Este arquivo contém informações básicas sobre o que cada uma das funcionalidades fornecidas pela HyperVec faz.

## Definição básica do vetor

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
- ``elem_size`` é o tamanho (em bytes) dos elementos individuais dentro do buffer. 
- ``buffer_size`` é o tamanho (em bytes) do vetor.
- ``used`` é o número de elementos já ocupados dentro do buffer (i.e., ocupados).

## Funções

``vec_alloc`` é o inicializador de todo vetor, ela aloca um vetor na memória com base num tamanho inicial de buffer.
``` C
int vec_alloc(Vec_t *vec, size_t init_buff_size, size_t elem_size);
```
**Parâmetros**:
- ``vec`` pointeiro para um vetor.
- ``init_buff_size`` tamanho inicial (em bytes) para a alocação do vetor.
- ``elem_size`` tamanho (em bytes) dos elementos individuais do vetor.

**Retorno**:
0 para sucesso, -1 se houver alguma falha
