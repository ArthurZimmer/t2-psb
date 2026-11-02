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
void* mymemory_alloc(mymemory_t *memory, size_t size){
    if (size == 0){
        printf("\ntamanho inválido.");
        return NULL;
    } else if (memory->total_size < size){
        printf("\ntamanho maior que o alocado anteriormente.");
        return NULL;
    } 

    memory->pool = malloc(size);

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