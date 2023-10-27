#include <stdio.h>
#include "LinkedList.c"

int main ()
{
    inicia();
    insereBlocoMemLivre(1800, 2200);
    insereBlocoMemLivre(2300, 400);
    exibeMemLivre();
    printf("\nEncontrou espaço disponível: %d\n", buscaEspacoDisp(300));
    printf("Enderço do Mínimo Bloco Suficiente: %d\n\n", minimo_bloco_suficiente(300));
    alocaMemoria(1234, 300);
    exibeMemLivre();
    return 0;
}
