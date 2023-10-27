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
    finalizaProcesso(3);
    exibeMemLivre();
    exibeMemAloc();
    organizaBlocoMemLivre();
    exibeMemLivre();
    exibeMemAloc();

    return 0;
}
