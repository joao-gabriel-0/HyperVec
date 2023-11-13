# Documentação da HyperVec

Este arquivo fornece informações sobre as funcionalidades da HyperVec, apresentadas na ordem em que estão definidas no arquivo "Hypervec.h".

---

## Definição da estrutura de vetor

O elemento fundamental da HyperVec é o tipo de dado `Vec_t`, definido da seguinte forma em "Hypervec.h":

``` C
typedef struct Vec_s {
    void *buffer;
    size_t elem_size;
    size_t buffer_size;
    size_t used;
} Vec_t;
```

Onde:
- `buffer` é um ponteiro para a memória onde os elementos do vetor são armazenados.
- `elem_size` é o tamanho dos elementos individuais dentro do buffer (em bytes).
- `buffer_size` é o tamanho do buffer (em bytes).
- `used` é o número de elementos ocupados dentro do buffer.

Você pode declarar um vetor `vec` da seguinte maneira:

``` C
Vec_t vec;
```

ou

``` C
struct Vec_s vec;
```

---

## Funções

### `vec_alloc`
Aloca um vetor com base em um tamanho de buffer inicial.

``` C
int vec_alloc(Vec_t *vec, size_t init_buff_size, size_t elem_size);
```

**Parâmetros**:
- `vec`: ponteiro para um vetor.
- `init_buff_size`: tamanho de alocação inicial do buffer (em bytes).
- `elem_size`: tamanho dos elementos do buffer (em bytes).

**Retorna**: 0 para sucesso, -1 para falha.

**Exemplo de uso:**
```C
Vec_t vec = {0};
vec_alloc(&vec, 20 * sizeof(int), sizeof(int));
```

### `vec_free`
Desaloca um vetor.

``` C
int vec_free(Vec_t *vec);
```

**Parâmetros**:
- `vec`: ponteiro para um vetor.

**Retorna**: 0 para sucesso, -1 para falha.

**Exemplo de uso:**
```C
vec_free(&vec);
```

### `vec_resize`
Aumenta ou diminui a capacidade de um vetor.

``` C
int vec_resize(Vec_t *vec, size_t new_buffer_size);
```

**Parâmetros**:
- `vec`: ponteiro para um vetor.
- `new_buffer_size`: novo tamanho de alocação do buffer do vetor (em bytes).

**Retorna**: 0 para sucesso, -1 para falha.

**Exemplo de uso:**
```C
// o vetor vec passará a ter 40 * tamanho de um int bytes
vec_resize(&vec, 40 * sizeof(int));

// o vetor vec passará a ter 20 * tamanho de um int bytes
vec_resize(&vec, 20 * sizeof(int));
```

### `vec_reset`
Define o número de elementos usados em um vetor como 0, efetivamente resetando seus elementos.

``` C
int vec_reset(Vec_t *vec);
```

**Parâmetros**:
- `vec`: ponteiro para um vetor.

**Retorna**: 0 para sucesso, -1 para falha.

**Exemplo de uso:**
```C
vec_reset(&vec);
```

### `vec_get`
Retorna o endereço de memória de um elemento específico de um vetor.

``` C
void *vec_get(Vec_t *vec, size_t index);
```

**Parâmetros**:
- `vec`: ponteiro para um vetor.
- `index`: índice do elemento desejado.

**Retorna**: Endereço do elemento desejado.

**Exemplo de uso:**
```C
void *addr = vec_get(&vec, 14);
```

### `vec_remove`
Remove um elemento de um vetor em um índice específico.

``` C
int vec_remove(Vec_t *vec, size_t index);
```

**Parâmetros**:
- `vec`: ponteiro para um vetor.
- `index`: índice do elemento desejado.

**Retorna**: 0 para sucesso, -1 para falha.

**Exemplo de uso:**
```C
// o elemento presente no índice 5 será removido do vetor
vec_remove(&vec, 5);
```

### `vec_push`
Empurra um elemento 'src' para o vetor.

``` C
int vec_push(Vec_t *vec, void *elem);
```

**Parâmetros**:
- `vec`: ponteiro para um vetor.
- `elem`: elemento de origem src.

**Retorna**: 0 para sucesso, -1 para falha.

**Exemplo de uso:**
```C
int value = 42;

// o valor 42 será armazenado no topo do vetor vec
vec_push(&vec, &value);
```

### `vec_pop`
Coloca o primeiro elemento de um vetor em 'dst'.

``` C
int vec_pop(Vec_t *vec, void *dst);
```

**Parâmetros**:
- `vec`: ponteiro para um vetor.
- `dst`: elemento de destino.

**Retorna**: 0 para sucesso, -1 para falha.

**Exemplo de uso:**
```C
int value;

// o primeiro valor presente no vetor vec será removido 
// deste vetor e armazenado na variável 'value' 
vec_pop(&vec, &value);
```

### `vec_insert`
Insere um elemento no vetor no índice.

``` C
int vec_insert(Vec_t *vec, void *elem, size_t index);
```

**Parâmetros**:
- `vec`: ponteiro para um vetor.
- `elem`: elemento de origem src.
- `index`: índice do elemento desejado.

**Retorna**: 0 para sucesso, -1 para falha.

**Exemplo de uso:**
```C
int value = 99;

// o valor 99 será inserido no índice 2 de vec
vec_insert(&vec, &value, 2);
```

### `vec_reverse`
Reorganiza os elementos de um vetor na ordem inversa (fim para início).

``` C
int vec_reverse(Vec_t *vec);
```

**Parâmetros**:
- `vec`: ponteiro para um vetor.

**Retorna**: 0 para sucesso, -1 para falha.

**Exemplo de uso:**
```C
// os elementos de vec serão organizados em ordem reversa
vec_reverse(&vec);
```

### `vec_copy`
Copia o conteúdo de 'src' para 'dst'.

``` C
int vec_copy(Vec_t *dst, Vec_t *src);
```

**Parâmetros**:
- `dst`: ponteiro para o vetor de destino.
- `src`: ponteiro para o vetor de origem.

**Retorna**: 0 para sucesso, -1 para falha.

**Exemplo de uso:**
```C
Vec_t new_vec = {0};

// new_vec passará a conter todos os elementos pertencentes em vec
vec_copy(&new_vec, &vec);
```

### `vec_append`
Anexa o conteúdo de 'src' a 'dst'.

``` C
int vec_append(Vec_t *dst, Vec_t *src);
```

**Parâmetros**:
- `dst`: ponteiro para o vetor de destino.
- `src`: ponteiro para o vetor de origem.

**Retorna**: 0 para sucesso, -1 para falha.

**Exemplo de uso:**
```C
// os elementos de new_vec serão pós-anexados em vec
vec_append(&vec, &new_vec);
```

### `vec_prepend`
Acrescenta o conteúdo de 'src' a 'dst'.

``` C
int vec_prepend(Vec_t *dst, Vec_t *src);
```

**Parâmetros**:
- `dst`: ponteiro para o vetor de destino.
- `src`: ponteiro para o vetor de origem.

**Retorna**: 0 para sucesso, -1 para falha.

**Exemplo de uso:**
```C
// os elementos de new_vec serão pré-anexados em vec
vec_prepend(&vec, &new_vec);
```

### `vec_compare`
Compara todos os elementos de 2 vetores (eles podem ter tamanhos arbitrários).

``` C
int vec_compare(Vec_t *vec1, Vec_t *vec2);
```

**Parâmetros**:
- `vec1`: vetor 1.
- `vec2`: vetor 2.

**Retorna**: 0 se forem todos iguais, -1 se não.

**Exemplo de uso:**
```C
int result = vec_compare(&vec, &new_vec);
```

### `vec_filter`
Filtra os elementos de src e os armazena em dst com base em uma função filter() definida pelo usuário.

``` C
int vec_filter(Vec_t *dst, Vec_t *src, bool (*filter)(void*));
```

**Parâmetros**:
- `dst`: ponteiro para o vetor de destino.
- `src`: ponteiro para o vetor de origem.
- `filter`: ponteiro para uma função de filtro.

**Retorna**: 0 se bem-sucedido, -1 se falhou.

**Exemplo de uso:**
```C
// definição da função de filtragem
static bool is_even(void *element) {
    return (*(int *) element % 2 == 0);
}

// somente os elementos inteiros pares serão armazenados em new_vec
vec_filter(&new_vec, &vec, is_even);
```

### `vec_iter`
Itera sobre os elementos de um vetor e chama uma função definida pelo usuário (iter()) para cada elemento iterado.

``` C
int vec_iter(Vec_t *vec, void (*iter)(void *));
```

**Parâmetros**:
- `vec`: ponteiro para um vetor.

**Retorna**: 0 se bem-sucedido, -1 se falhou.

**Exemplo de uso:**
```C
// definição de uma função iteradora
static void sum_int(void *element) {
    *(int *) element += 1;
}

// isso irá incrementar cada elemento do vetor
vec_iter(&vec, sum_int);
```
