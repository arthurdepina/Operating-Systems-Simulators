/*
 *              Simulador de Gerenciamento de Memória                
 * Grupo:
 * Arthur de Pina Balduino Leitão - 32207840
 * João Victor Dallapé Madeira    - 32209592
 * David Varão Lima Bentes Pessoa - 32253133
 * Disponível em:
 * https://github.com/arthurdepina/Sistemas-Operacionais-Trabalho-01
 * https://replit.com/@arthurdepina/Sistemas-Operacionais-Trabalho-01
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "LinkedList.c"

int main()
{
    inicia();

    int mem_disp;
    bool exec = true;
    int numero_processo;
    int mem_necessaria;

    printf("\nQuantidade de memória (KB) disponível? ");
    scanf("%d", &mem_disp);
    if (mem_disp <= 0) {
        printf("A quantidade memória precisa ser um número inteiro maior que zero.\n");
        main();
    }
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

            printf("Número do Processo? ");
            scanf("%d", &numero_processo); printf("\n");
            printf("Memória Necessária? ");
            scanf("%d", &mem_necessaria); printf("\n");
            alocaMemoria(numero_processo, mem_necessaria);
            del_bloco_mem_livre();
            break;

        case 2:

            printf("Número do Processo? ");
            scanf("%d", &numero_processo); printf("\n");
            if (valida_processo_remover(numero_processo)) {
                finalizaProcesso(numero_processo);
                organizaBlocoMemLivre();
                break;
            } else {
                break;
            }

        case 3:

            exibeMemLivre();
            break;

        case 4:

            exibeMemAloc();
            break;

        case 5:

            exibeMemLivre();
            exibeMemAloc();
            break;

        case 6:

            printf("\nPrograma Finalizado\n\n\n");
            liberaLista();
            exec = false;
            break;

        default:

            printf("Por favor, selecione uma opção válida\n");
            break;
        }
    }
    return 0;
}
