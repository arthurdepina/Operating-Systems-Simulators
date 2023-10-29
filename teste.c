#include <stdio.h>
#include "LinkedList.c"

int main ()
{
    inicia();
    insereBlocoMemLivre(0, 4000);
    alocaMemoria(1, 1800);
    alocaMemoria(2, 300);
    alocaMemoria(3, 100);
    exibeMemLivre();
    exibeMemAloc();
    printf("====\n");
    finalizaProcesso(2);
    organizaBlocoMemLivre();
    exibeMemLivre();
    exibeMemAloc();
    printf("\n====\n");
    alocaMemoria(4, 400);
    exibeMemLivre();
    exibeMemAloc();
    printf("quanta memória livre: %d\n", quantaMemoriaLivre());
    printf("quanta memória alocada: %d\n", quantaMemoriaAloc());
    exibeProcesso(4);
    // exibeMemLivre();
    // exibeMemAloc();
    // finalizaProcesso(1);
    // organizaBlocoMemLivre();
    // printf("\n====\n");
    // exibeMemLivre();
    // exibeMemAloc();
    // printf("\n====\n");
    // finalizaProcesso(2);
    // organizaBlocoMemLivre();
    // exibeMemLivre();
    // exibeMemAloc();
    // printf("\n====\n");
    liberaLista();

    return 0;
}
