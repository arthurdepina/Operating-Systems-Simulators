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

int minimo_bloco_suficiente(int Tam, int End);

int buscaEspacoDisp (int Tam);

tipo_MemLivre* merge(tipo_MemLivre *a, tipo_MemLivre *b);
tipo_MemLivre* mergeSort(tipo_MemLivre *head);

tipo_MemAloc* merge_aloc(tipo_MemAloc *a, tipo_MemAloc *b);
tipo_MemAloc* mergeSort_aloc(tipo_MemAloc *head);

void organizaBlocoMemAloc();

int valida_memoria(int mem);

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
        printf("{ Address: %d, Size: %d } => ", aux->End_i, aux->tam);
        aux = aux->prox;
    }
    printf("NULL\n");
}

void exibeMemAloc (void)
{
    tipo_MemAloc *aux = inicioMemAloc;
    printf("Memória Alocada:\n");
    while (aux) {
        printf("{ NProcess: %d, Address: %d, Size: %d } => ", aux->NProcesso,
                                                              aux->End_i,
                                                              aux->tam);
        aux = aux->prox;
    }
    printf("NULL\n");
}

/* Aloca bloco de memória para processo*/
void alocaMemoria (int nProcesso, int Tam)
{
    if (!valida_memoria(Tam)) return;

    int end_alt_1 = buscaEspacoDisp(Tam);
    if (end_alt_1 == -1) {
        printf("ERRO: Não foi possível alocar memória para esse processo.\n");
        return;
    }

    // endereço do bloco de memória que será alocado
    int end_mem = minimo_bloco_suficiente(Tam, end_alt_1);

    tipo_MemLivre *atual = inicioMemLivre;
    while (atual) {
        if (atual->End_i == end_mem) {

            int novo_end_aloc  = atual->End_i;
            insereBlocoAloc(nProcesso, novo_end_aloc, Tam);

            atual->tam   = atual->tam - Tam;
            atual->End_i = atual->End_i + Tam;
            organizaBlocoMemAloc();
            return;
        }
        atual = atual->prox;
    }
}

/* Verifica se há espaço de memória disponível */
int buscaEspacoDisp (int Tam)
{
    tipo_MemLivre *atual = inicioMemLivre;

    while (atual) {
        if (atual->tam >= Tam) return atual->End_i;
        atual = atual->prox;
    }
    return -1;
}

void organizaBlocoMemLivre (void)
{
    inicioMemLivre = mergeSort(inicioMemLivre);
    tipo_MemLivre *atual = inicioMemLivre;
    while (atual) {
        while (atual->prox) {
            if (atual->End_i + atual->tam == atual->prox->End_i) {
                atual->tam += atual->prox->tam;
                tipo_MemLivre *apagar = atual->prox;
                atual->prox = atual->prox->prox;
                free(apagar);
            }
            else break;
        }
        atual = atual->prox;
    }
}

void finalizaProcesso(int n)
{
    tipo_MemAloc *atual = inicioMemAloc;

    while (atual) {
        if (atual->NProcesso == n) {
            insereBlocoMemLivre(atual->End_i, atual->tam);
            inicioMemAloc = atual->prox;
            free(atual);
            return;
        }
        if (atual->prox->NProcesso == n) {
            insereBlocoMemLivre(atual->prox->End_i, atual->prox->tam);
            tipo_MemAloc *apagar = atual->prox;
            atual->prox = atual->prox->prox;
            free(apagar);
            return;
        }
        atual = atual->prox;
    }

    printf("Processo não encontrado");
}

void liberaLista (void)
{
    tipo_MemLivre *atual_livre = inicioMemLivre;
    tipo_MemLivre *proximo_livre = inicioMemLivre;
    tipo_MemAloc *atual_aloc = inicioMemAloc;
    tipo_MemAloc *proximo_aloc = inicioMemAloc;

    while (atual_livre) {
        proximo_livre = atual_livre->prox;
        free(atual_livre);
        atual_livre = proximo_livre;
    }

    while (atual_aloc) {
        proximo_aloc = atual_aloc->prox;
        free(atual_aloc);
        atual_aloc = proximo_aloc;
    }

    inicioMemLivre = NULL;
    inicioMemAloc = NULL;
}

// Extras

/* Função utilizada para retornar o endereço do
 * menor bloco de memória suficiente para o processo */
int minimo_bloco_suficiente(int Tam, int End)
{
    tipo_MemLivre *atual  = inicioMemLivre;
    int minimo_suficiente;
    int end_minimo_suf = End;
    while (atual) {
        if (atual->End_i == End) {
            minimo_suficiente = atual->tam;
        }
        if (atual->tam >= Tam && atual->tam < minimo_suficiente) {
            minimo_suficiente = atual->tam;
            end_minimo_suf = atual->End_i;
        }
        atual = atual->prox;
    }
    return end_minimo_suf;
}

/* Merge para ordenar a Lista de Memória Livre*/
tipo_MemLivre* merge(tipo_MemLivre *a, tipo_MemLivre *b) {
    if (!a)
        return b;
    if (!b)
        return a;

    tipo_MemLivre *result = NULL;

    if (a->End_i <= b->End_i) {
        result = a;
        result->prox = merge(a->prox, b);
    } else {
        result = b;
        result->prox = merge(a, b->prox);
    }
    return result;
}

/* Merge Sort para ordenar a Lista de Memória Livre*/
tipo_MemLivre* mergeSort(tipo_MemLivre *head) {
    if (!head || !head->prox)
        return head;

    tipo_MemLivre *middle = head;
    tipo_MemLivre *fast = head->prox;

    while (fast && fast->prox) {
        middle = middle->prox;
        fast = fast->prox->prox;
    }

    tipo_MemLivre *half = middle->prox;
    middle->prox = NULL;

    return merge(mergeSort(head), mergeSort(half));
}

// Adaptando as funções para tipo_MemAloc:

tipo_MemAloc* merge_aloc(tipo_MemAloc *a, tipo_MemAloc *b) {
    if (!a)
        return b;
    if (!b)
        return a;

    tipo_MemAloc *result = NULL;

    if (a->End_i <= b->End_i) {
        result = a;
        result->prox = merge_aloc(a->prox, b);
    } else {
        result = b;
        result->prox = merge_aloc(a, b->prox);
    }
    return result;
}

tipo_MemAloc* mergeSort_aloc(tipo_MemAloc *head) {
    if (!head || !head->prox)
        return head;

    tipo_MemAloc *middle = head;
    tipo_MemAloc *fast = head->prox;

    while (fast && fast->prox) {
        middle = middle->prox;
        fast = fast->prox->prox;
    }

    tipo_MemAloc *half = middle->prox;
    middle->prox = NULL;

    return merge_aloc(mergeSort_aloc(head), mergeSort_aloc(half));
}

void organizaBlocoMemAloc()
{
    inicioMemAloc = mergeSort_aloc(inicioMemAloc);
}

int valida_memoria(int mem)
{
    if (mem <= 0) {
        printf("ERRO: A quantidade de memória deve ser um número inteiro maior que zero.");
        return 0;
    } else {
        return 1;
    }
}

