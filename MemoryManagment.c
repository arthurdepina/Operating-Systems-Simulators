#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "LinkedList.c"

int main()
{
    int mem_disp;
    bool exec = true;

    printf("Quantidade de memória disponível? ");
    scanf("%d", &mem_disp);
    while(exec)
    {
        int opcao_selecionada = 0;
        printf("\nMENU\n");
        printf("1 - Alocar Memoria Para Processo\n");
        printf("2 - Liberar Memoria de Processo\n");
        printf("3 - Mostrar Memoria Disponivel\n");
        printf("4 - Mostrar Memoria Alocada\n");
        printf("5 - Sair\n");
        printf("Selecione: ");
        scanf("%d", &opcao_selecionada); printf("\n");
        switch (opcao_selecionada)
        {
        case 1:
            /* Pergunta quanta memória deseja alocar 
             * Verifica se há memória disponível suficiente
             * Se houver memíria diponível suficiente
             *      aloca e retorna que a memória foi alocada com sucesso
             * Se nao
             *      Informa que ha memória diponível suficiente
             *      Informa quanta memória diponível há*/
            break;
        case 2:
            /* Libera memória do processo selecionado.
             * Se o processo não existe, informa o usuário. */
            break;
        case 3:
            /* Mostra memória disponível */
            break;
        case 4:
            /*Mostra memória ocupada*/
            break;
        case 5:
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
