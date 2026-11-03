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

}

// exibe todas alocações + início e tamanho
void mymemory_display(mymemory_t *memory){

}

// exibe estatísticas da memória: 
//  - número de alocações
//  - memória total alocada
//  - memória total livre
//  - maior bloco contíguo de memória livre
//  - número de fragmentos da memória livre (qtd de blocos de memória entre alocações)
void mymemory_stats(mymemory_t *memory){

}

// libera todos os recursos (alocações e o bloco de memória atual)
void mymemory_cleanup(mymemory_t *memory){
    
}