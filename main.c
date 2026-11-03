
#include <stdio.h>
#include "mymemory.h"

int main(void) {
    mymemory_t *memory = NULL;
    int option = -1;
    size_t size;

    while (option != 0) {
        printf("\n========== MYMEMORY ==========\n");
        printf("1 - Inicializar pool de memoria\n");
        printf("2 - Alocar memoria\n");
        printf("3 - Liberar bloco de memoria\n");
        printf("4 - Exibir alocacoes\n");
        printf("5 - Exibir estatisticas\n");
        printf("6 - Limpar memoria (cleanup)\n");
        printf("0 - Sair\n");
        printf("================================\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &option) != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            option = -1;
            printf("\nOpcao invalida.\n");
            continue;
        }

        switch (option) {

            case 1:
                if (memory != NULL) {
                    printf("\nO pool ja foi inicializado.\n");
                    break;
                }

                printf("\nDigite o tamanho do pool (em bytes): ");
                if (scanf("%zu", &size) != 1) {
                    printf("\nTamanho invalido.\n");
                    break;
                }

                memory = mymemory_init(size);

                if (memory == NULL) {
                    printf("\nErro ao inicializar memoria\n");
                } else {
                    printf("\nPool inicializado com %zu bytes\n", size);
                }
                break;

            case 2:
                if (memory == NULL) {
                    printf("\nInicialize o ppol primeiro\n");
                    break;
                }

                printf("\nDigite o tamanho da alocacao (em bytes): ");
                if (scanf("%zu", &size) != 1) {
                    printf("\nTamanho invalido.\n");
                    break;
                }

                void *ptr = mymemory_alloc(memory, size);

                if (ptr == NULL) {
                    printf("\nNao foi possivel alocar memoria.\n");
                } else {
                    printf("\nMemoria alocada com sucesso!\n");
                    printf("Endereco: %p\n", ptr);
                    printf("Tamanho: %zu bytes\n", size);
                }
                break;

            case 3:
                if (memory == NULL) {
                    printf("\nInicialize o ppol primeiro.\n");
                    break;
                }

                if (memory->head == NULL) {
                    printf("\nNao existem blocos alocados.\n");
                    break;
                }

                printf("\nBlocos alocados:\n");

                allocation_t *aux = memory->head;
                int count = 1;

                while (aux != NULL) {
                    printf("%d - Endereco: %p | Tamanho: %zu bytes\n",
                           count, aux->start, aux->size);
                    aux = aux->next;
                    count++;
                }

                int selected;
                printf("\nDigite o numero do bloco para liberar: ");

                if (scanf("%d", &selected) != 1) {
                    printf("\nOpcao invalida.\n");
                    break;
                }

                if (selected < 1 || selected >= count) {
                    printf("\nBloco invalido.\n");
                    break;
                }

                aux = memory->head;

                for (int i = 1; i < selected; i++) {
                    aux = aux->next;
                }

                mymemory_free(memory, aux->start);
                printf("\nBloco liberado com sucesso.\n");
                break;

            case 4:
                if (memory == NULL) {
                    printf("\nInicialize o pool primeiro.\n");
                    break;
                }

                printf("\n=== ALOCACOES ATUAS ===\n");
                mymemory_display(memory);
                break;

            case 5:
                if (memory == NULL) {
                    printf("\nInicialize o pool primeiro.\n");
                    break;
                }

                printf("\n=== ESTATISTICAS ===\n");
                mymemory_stats(memory);
                break;

            case 6:
                if (memory == NULL) {
                    printf("\nNenhum pool inicializado.\n");
                    break;
                }

                mymemory_cleanup(memory);
                memory = NULL;

                printf("\nMemoria liberada com sucesso.\n");
                break;

            case 0:
                printf("\nEncerrando programa...\n");
                break;

            default:
                printf("\nOpcao invalida.\n");
                break;
        }

    };

    if (memory != NULL) {
        mymemory_cleanup(memory);
        memory = NULL;
    }

    return 0;
}
