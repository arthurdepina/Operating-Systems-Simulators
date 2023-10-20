#include <stdio.h>
#include <stdlib.h>

typedef struct _tipo_MemLivre
{
    int End_i;
    int tam;
    struct _tipo_MemLivre *prox;
} tipo_MemLivre;

typedef struct _tipo_MemAloc
{
    int NProcesso;
    int End_i;
    int tam;
    struct _tipo_MemAloc *prox;
} tipo_MemAloc;

void inicia (void)
{

}

void insereBlocoAloc (int nProcesso, int end_i, int tam)
{

}

void insereBlocoMemLivre (int end_i, int tam)
{

}

int alocaMemoria (int nProcesso, int Tam)
{

}

int buscaEspacoDisp (int Tam)
{

}

void finalizProcesso (int n)
{

}

void organizaBlocoMemLivre (void)
{

}

void liberaLista (void)
{
    
}
