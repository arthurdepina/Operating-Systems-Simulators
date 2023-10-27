#include <stdio.h>
#include "LinkedList.c"

int main ()
{
    inicia();
    insereBlocoMemLivre(1800, 2200);
    insereBlocoMemLivre(2300, 400);
    exibeMemLivre();
    printf("%d\n", buscaEspacoDisp(300));
    printf("%d\n", minimo_bloco_suficiente(300));
    return 0;
}
