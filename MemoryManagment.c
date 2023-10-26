#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "LinkedList.c"

int main()
{
    int mem_disp;
    bool exec = true;

    printf("Quantidade de memória (KB) disponível? ");
    scanf("%d", &mem_disp);
    insereBlocoMemLivre(0, mem_disp);

    while(exec)
    {
        int opcao_selecionada = 0;
        printf("\nMENU\n");
        printf("1 - Inserir Processo\n");
        printf("2 - Encerrar Processo\n");
        printf("3 - Mostrar Memoria Livre\n");
        printf("4 - Mostrar Memoria Alocada\n");
        printf("5 - Exibir Situação da Memória\n");
        printf("6 - Sair\n");
        printf("Selecione: ");
        scanf("%d", &opcao_selecionada); printf("\n");
        switch (opcao_selecionada)
        {
        case 1:
            /* Pergunta quanta memória deseja alocar 
             * Verifica se há memória disponível suficiente
             * Se houver memória diponível suficiente
             *      aloca e retorna que a memória foi alocada com sucesso
             * Se nao
             *      Informa que ha memória diponível suficiente
             *      Informa quanta memória diponível há */
            int n_processo;
            int tam_processo;
            printf("Número do processo? ");
            scanf("%d", &n_processo);
            printf("\nMemória necessária para o processo? ");
            scanf("%d", &tam_processo); printf("\n");
            if (buscaEspacoDisp) {
                alocaMemoria(n_processo, tam_processo);
                printf("Programa Inserido Com Sucesso\n");
            } else {
                printf("Não foi possível alocar o processo.\n");
                printf("Apenas %d KB de memória disponível.\n", quantMemoriaDisp());
            }
            break;
        case 2:
            /* Libera memória do processo selecionado.
             * Se o processo não existe, informa o usuário. */
            printf("Deseja encerrar qual processo? ");
            scanf("%d", &n_processo);
            finalizaProcesso(n_processo);
            break;
        case 3:
            /* Mostra memória disponível */
            exibeMemLivre();
            break;
        case 4:
            /*Mostra memória ocupada*/
            exibeMemAloc();
            break; 
        case 5:
            exibeMemLivre();
            exibeMemAloc();
            break;
        case 6:
            printf("\nPrograma Finalizado\n\n");
            exec = false;
            break;
        default:
            printf("Por favor, selecione uma opção válida\n");
            break;
        }
    }

    return 0;
}


/*
    insereBlocoMemLivre(100, 50);
    insereBlocoMemLivre(150, 30);
    insereBlocoAloc(1, 200, 10);
    insereBlocoAloc(2, 210, 20);
    exibeMemLivre();
    exibeMemAloc();
*/
