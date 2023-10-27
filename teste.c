#include <stdio.h>
#include "LinkedList.c"

int main ()
{
    inicia();
    insereBlocoMemLivre(0, 4000);
    alocaMemoria(1, 1800);
    alocaMemoria(2, 300);
    exibeMemLivre();
    exibeMemAloc();
    finalizaProcesso(1);
    organizaBlocoMemLivre();
    exibeMemLivre();
    exibeMemAloc();
    finalizaProcesso(2);
    organizaBlocoMemLivre();
    exibeMemLivre();
    exibeMemAloc();

    return 0;
}
