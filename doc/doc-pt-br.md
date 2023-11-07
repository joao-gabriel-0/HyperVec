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
