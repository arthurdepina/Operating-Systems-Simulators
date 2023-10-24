#include <stdio.h>
#include <stdlib.h>

typedef struct _tipo_MemLivre {
    int End_i;
    int tam;
    struct _tipo_MemLivre *prox;
} tipo_MemLivre;

typedef struct _tipo_MemAloc {
    int NProcesso;
    int End_i;
    int tam;
    struct _tipo_MemAloc *prox;
} tipo_MemAloc;

tipo_MemLivre *inicioMemLivre = NULL;
tipo_MemAloc  *inicioMemAloc  = NULL;

void inicia (void)
{
    inicioMemLivre = NULL;
    inicioMemAloc  = NULL;
}

void insereBlocoAloc (int nProcesso, int end_i, int tam)
{
    tipo_MemAloc *novo = (tipo_MemAloc *) calloc (tam, sizeof(tipo_MemAloc));

    if (!novo) {
        printf("Error. FAILED MEMORY ALOCATION.\n");
        exit(1);
    }

    novo->NProcesso = nProcesso;
    novo->End_i     = end_i;
    novo->tam       = tam;
    novo->prox      = NULL;

    if (!inicioMemAloc) {
        inicioMemAloc = novo;
    } else {
        tipo_MemAloc *aux = inicioMemAloc;
        while (aux->prox) {
            aux = aux->prox;
        }
        aux->prox = novo;
    }
}

void insereBlocoMemLivre (int end_i, int tam)
{
    tipo_MemLivre *novo = (tipo_MemLivre *) calloc (tam, sizeof(tipo_MemAloc));

    if (!novo) {
        printf("Error. FAILED MEMORY ALOCATION.\n");
        exit(1);
    }

    novo->End_i = end_i;
    novo->tam   = tam;
    novo->prox  = NULL;

    if (!inicioMemLivre) {
        inicioMemLivre = novo;
    } else {
        tipo_MemLivre *aux = inicioMemLivre;
        while (aux->prox) {
            aux = aux->prox;
        }
        aux->prox = novo;
    }
}

void exibeMemLivre (void)
{
    tipo_MemLivre *aux = inicioMemLivre;
    printf("Free Memory:\n");
    while (aux) {
        printf("Address: %d, Size: %d\n", aux->End_i, aux->tam);
        aux = aux->prox;
    }
}

void exibeMemAloc (void)
{
    tipo_MemAloc *aux = inicioMemAloc;
    printf("Free Memory:\n");
    while (aux) {
        printf("NProcess: %d, Address: %d, Size: %d\n", aux->NProcesso,
                                                        aux->End_i,
                                                        aux->tam);
        aux = aux->prox;
    }
}

/* Aloca bloco de memória para processo*/
int alocaMemoria (int nProcesso, int Tam)
{

}

/* Verifica se há espaço de memória disponível */
int buscaEspacoDisp (int Tam)
{

}

void organizaBlocoMemLivre (void)
{

}

void finalizaProcesso(void)
{

}

void liberaLista (void)
{
    
}
