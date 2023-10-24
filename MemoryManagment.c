#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.c"

int main()
{
    int mem_disp;

    inicia();
    insereBlocoMemLivre(100, 50);
    insereBlocoMemLivre(150, 30);
    insereBlocoAloc(1, 200, 10);
    insereBlocoAloc(2, 210, 20);

    /*
    printf("Quantidade de memória disponível? ");
    scanf("%d", &mem_disp);
    */

    exibeMemLivre();
    exibeMemAloc();
    return 0;
}
