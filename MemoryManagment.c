#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.c"

void finalizProcesso (int n)
{

}

int main()
{
    inicia();
    insereBlocoMemLivre(100, 50);
    insereBlocoMemLivre(150, 30);
    insereBlocoAloc(1, 200, 10);
    insereBlocoAloc(2, 210, 20);

    exibeMemLivre();
    exibeMemAloc();
    return 0;
}
