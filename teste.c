#include <stdio.h>
#include "LinkedList.c"

int main ()
{
    inicia();
    insereBlocoMemLivre(0, 4000);
    alocaMemoria(1, 1800);
    alocaMemoria(2, 300);
    alocaMemoria(3, 100);
    printf("====\n");
    exibeMemLivre();
    exibeMemAloc();
    finalizaProcesso(3);
    organizaBlocoMemLivre();
    printf("\n====\n");
    exibeMemLivre();
    exibeMemAloc();
    finalizaProcesso(1);
    organizaBlocoMemLivre();
    printf("\n====\n");
    exibeMemLivre();
    exibeMemAloc();
    printf("\n====\n");
    finalizaProcesso(2);
    organizaBlocoMemLivre();
    exibeMemLivre();
    exibeMemAloc();
    printf("\n====\n");

    return 0;
}
