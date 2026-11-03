#include <stdio.h>
#include <stdlib.h>
#include "mymemory.h"


// alocar bloco de memoria e retornar ponteiro pra ele
mymemory_t* mymemory_init(size_t size){
    if (size == 0){
        printf("\ntamanho inválido.");
        return NULL;
    } 

    mymemory_t* aux = malloc(sizeof(mymemory_t));

    aux->pool = malloc(size);
    aux->total_size = size;
    aux->head = NULL;

    return aux;
}

// tenta alocar bloco de memoria em tamanho especifico
// se for bem sucedido, retorna ponteiro pro inicio do bloco
// se não, retorna NULL
void* mymemory_alloc(mymemory_t *memory, size_t size) {
    if (memory == NULL || size == 0) {
        return NULL;
    }
    if (size > memory->total_size || memory->pool == NULL) {
        return NULL;
    }

    // node atual
    allocation_t* aux = memory->head;
    // node anterior
    allocation_t* previous = NULL;
    // guarda a alocação em char
    char* position = (char*)memory->pool;

    // alocacoes
    while (aux != NULL) {
        size_t space_free = (char*)aux->start - position;

        if (space_free >= size) {
            break;
        }

        position = (char*)aux->start + aux->size;
        previous = aux;
        aux = aux->next;
    }

    if (aux == NULL) {
        char* pool_end = (char*)memory->pool + memory->total_size;
        size_t space_free = pool_end - position;

        if (space_free < size) {
            return NULL;
        }
    }

    allocation_t* new_node = malloc(sizeof(allocation_t));

    if (new_node == NULL) {
        return NULL;
    }

    new_node->start = position;
    new_node->size = size;
    new_node->next = aux;

    if (previous == NULL) {
        memory->head = new_node;
    } else {
        previous->next = new_node;
    }

    return new_node->start;
}

// libera a alocação apontada por *ptr
// se *ptr não for válido o método não faz nada
void mymemory_free(mymemory_t *memory, void *ptr){
    if (memory == NULL || ptr == NULL) {
        return;
    }

    // node atual
    allocation_t* aux = memory->head;
    // node anterior
    allocation_t* previous = NULL;

    while (aux != NULL) {
        if (aux->start == ptr) {
            if (previous == NULL) {
                memory->head = aux->next;
            } else {
                previous->next = aux->next;
            }
            free(aux);
            return;
        }

        previous = aux;
        aux = aux->next;
    }
}

// exibe todas alocações + início e tamanho
void mymemory_display(mymemory_t *memory){
    if (memory == NULL) {
        return;
    }

    printf("\n--- Alocações atuais ---\n");

    if (memory->head == NULL) {
        printf("(nenhuma)\n");
        return;
    }

    allocation_t* aux = memory->head;
    int i = 0;

    while (aux != NULL) {
        size_t offset = (char*)aux->start - (char*)memory->pool;
        printf("#%d  início: %p  offset: %zu  tamanho: %zu\n", i, aux->start, offset, aux->size);
        i++;
        aux = aux->next;
    }
}

// exibe estatísticas da memória: 
//  - número de alocações
//  - memória total alocada
//  - memória total livre
//  - maior bloco contíguo de memória livre
//  - número de fragmentos da memória livre (qtd de blocos de memória entre alocações)
void mymemory_stats(mymemory_t *memory){
    if (memory == NULL) {
        return;
    }

    // node atual
    allocation_t* aux = memory->head;
    // guarda o início da lacuna atual em char
    char* position = (char*)memory->pool;
    // fim do pool
    char* pool_end = (char*)memory->pool + memory->total_size;

    int num_allocations = 0;
    size_t total_allocated = 0;
    size_t largest_free = 0;
    int fragments = 0;

    while (1) {
        // fim da lacuna atual: início do próximo node ou fim do pool
        char* gap_end = pool_end;
        if (aux != NULL) {
            gap_end = (char*)aux->start;
        }

        size_t space_free = gap_end - position;

        if (space_free > 0) {
            fragments++;
            if (space_free > largest_free) {
                largest_free = space_free;
            }
        }

        if (aux == NULL) {
            break;
        }

        num_allocations++;
        total_allocated += aux->size;
        position = (char*)aux->start + aux->size;
        aux = aux->next;
    }

    printf("\n--- Estatísticas ---\n");
    printf("Número de alocações: %d\n", num_allocations);
    printf("Memória alocada: %zu bytes\n", total_allocated);
    printf("Memória livre: %zu bytes\n", memory->total_size - total_allocated);
    printf("Maior bloco livre contíguo: %zu bytes\n", largest_free);
    printf("Fragmentos livres: %d\n", fragments);
}

// libera todos os recursos (alocações e o bloco de memória atual)
void mymemory_cleanup(mymemory_t *memory){
    if (memory == NULL) {
        return;
    }

    allocation_t *aux = memory->head;

    while (aux != NULL) {
        allocation_t *next = aux->next;
        free(aux);
        aux = next;
    }

    free(memory->pool);
    free(memory);
}