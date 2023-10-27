#include <stdio.h>
#include "LinkedList.c"

int main ()
{
    inicia();
    // insereBlocoMemLivre(1800, 2200);
    // insereBlocoMemLivre(2300, 400);
    // exibeMemLivre();
    // printf("\nEncontrou espaço disponível: %d\n", buscaEspacoDisp(300));
    // printf("Enderço do Mínimo Bloco Suficiente: %d\n\n", minimo_bloco_suficiente(300));
    // alocaMemoria(1234, 300);
    // exibeMemLivre();
    insereBlocoMemLivre(0, 4000);
    alocaMemoria(1234, 1800);
    exibeMemLivre();
    exibeMemAloc();
    alocaMemoria(5678, 300);
    exibeMemLivre();
    exibeMemAloc();

    return 0;
}
