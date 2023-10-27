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
    tipo_MemLivre *novo = (tipo_MemLivre *) calloc (tam, sizeof(tipo_MemLivre));

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
    printf("Memória Livre:\n");
    while (aux) {
        printf("Address: %d, Size: %d\n", aux->End_i, aux->tam);
        aux = aux->prox;
    }
}

void exibeMemAloc (void)
{
    tipo_MemAloc *aux = inicioMemAloc;
    printf("Memória Alocada:\n");
    while (aux) {
        printf("NProcess: %d, Address: %d, Size: %d\n", aux->NProcesso,
                                                        aux->End_i,
                                                        aux->tam);
        aux = aux->prox;
    }
}

/* Aloca bloco de memória para processo*/
void alocaMemoria (int nProcesso, int Tam)
{
    // int end_mem = buscaEspacoDisp(-1); // endereço do bloco de memória que será alocado
    // tipo_MemLivre *atual = inicioMemLivre;
    // while (atual) {
    //     if (atual->End_i = end_mem) {
    //         atual->tam = atual->tam - Tam;
    //         int novo_end = atual->End_i + atual->tam + Tam;
    //         // insereBlocoMemLivre();
    //     }
    // }

}

/* Verifica se há espaço de memória disponível */
int buscaEspacoDisp (int Tam)
{
    tipo_MemLivre *atual = inicioMemLivre;

    while (atual) {
        if (atual->tam >= Tam) return 1;
        atual = atual->prox;
    }
    return 0;
}

void organizaBlocoMemLivre (void)
{

}

void finalizaProcesso(int n)
{

}

void liberaLista (void)
{
    
}

// Extras

/* Função utilizada para retornar o endereço do
 * menor bloco de memória suficiente para o processo */
int minimo_bloco_suficiente(int Tam)
{
    tipo_MemLivre *atual  = inicioMemLivre;
    int minimo_suficiente = atual->tam;
    int end_minimo_suf    = atual->End_i;
    while (atual) {
        if (atual->tam >= Tam && atual->tam < minimo_suficiente) {
            minimo_suficiente = atual->tam;
            end_minimo_suf    = atual->End_i;
        }
        atual = atual->prox;
    }
    printf("end_minimo_suf: %d\n", end_minimo_suf);
    return end_minimo_suf;
}

int quantMemoriaDisp () 
{

}

int quantMemoriaOcup ()
{
    
}

int buscaProcesso ()
{

}
