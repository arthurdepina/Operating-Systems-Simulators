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

// Declarando algumas funções

int minimo_bloco_suficiente(int Tam, int End);

int buscaEspacoDisp (int Tam);

tipo_MemLivre* merge(tipo_MemLivre *a, tipo_MemLivre *b);
tipo_MemLivre* mergeSort(tipo_MemLivre *head);

tipo_MemAloc* merge_aloc(tipo_MemAloc *a, tipo_MemAloc *b);
tipo_MemAloc* mergeSort_aloc(tipo_MemAloc *head);

void organizaBlocoMemAloc();

int valida_memoria(int mem);

// Fim das declarações de funções

void inicia (void)
{
    inicioMemLivre = NULL;
    inicioMemAloc  = NULL;
}

/* Insere bloco de memória alocada na lista encadeada.
 * Começa declarando um nó novo. Assinala os valores para esse nó.
 * Verifica se será o primeiro nó. Caso contrário, busca pelo fim
 * da lista encadeada e se insere.                              */
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

/* Insere bloco de memória alocada na lista encadeada.
 * Começa declarando um nó novo. Assinala os valores para esse nó.
 * Verifica se será o primeiro nó. Caso contrário, busca pelo fim
 * da lista encadeada e se insere.                              */
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

/* Exibe memória livre.
 * Passa por cada nós da lista de memória livre e exibe o nó. */
void exibeMemLivre (void)
{
    tipo_MemLivre *aux = inicioMemLivre;
    printf("Memória Livre:\n");
    while (aux) {
        printf("{ End_i: %d, tam: %d } => ", aux->End_i, aux->tam);
        aux = aux->prox;
    }
    printf("NULL\n");
}

/* Exibe memória alocada.
 * Passa por cada nós da lista de memória alocada e exibe o nó. */
void exibeMemAloc (void)
{
    tipo_MemAloc *aux = inicioMemAloc;
    printf("Memória Alocada:\n");
    while (aux) {
        printf("{ NProcesso: %d, End_i: %d, tam: %d } => ", aux->NProcesso,
                                                            aux->End_i,
                                                            aux->tam);
        aux = aux->prox;
    }
    printf("NULL\n");
}

/*                  Aloca bloco de memória para processo. 

 * Verifica se o tamanho inserido para memória é valido.

 * Em seguida busca um nó da memória livre que tenha memória suficiente para
 * alocar o processo. Se não houver nenhum bloco disponível, avisa o usuário.
 * Se houver um nó com espaço suficiente para o processo, salva o endereço
 * desse bloco na variável alternativa_para_endereço. Não usaremos esse
 * endereço necessariamente, pois pode haver um bloco com um espaço menor que
 * também seja suficiente. Encontraremos o menor bloco suficiente para armazenar
 * o processo em minimo_bloco_suficiente, armazenamos o endereço desse bloco
 * em end_mem.
 * 
 * Procuramos então o nó da memória livre com endereço end_mem, e usamos esse
 * endereço para alocar o bloco de memória alocada. Em seguida diminuimos o
 * tanto de memória disponível no bloco de memória livre selecionado e alteramos
 * o endereço desse bloco.
 * 
 * Em seguida nós ordenamos o bloco de memória alocada de acordo com os
 * endereços.                                                                 */
void alocaMemoria (int nProcesso, int Tam)
{
    if (!valida_memoria(Tam)) return;

    // Verifica se há nó com espaço de memória suficiente para o processo.
    int alternativa_para_endereco = buscaEspacoDisp(Tam);
    if (alternativa_para_endereco == -1) {
        printf("ERRO: Não foi possível alocar memória para esse processo.\n");
        return;
    }

    // endereço do bloco de memória que será alocado
    int end_mem = minimo_bloco_suficiente(Tam, alternativa_para_endereco);

    tipo_MemLivre *atual = inicioMemLivre;
    while (atual) {
        if (atual->End_i == end_mem) {

            int novo_end_aloc  = atual->End_i;
            insereBlocoAloc(nProcesso, novo_end_aloc, Tam);

            // Alterando tamanho disponível e endereço do nó de
            // memória livre em que o processo foi armazenado.
            atual->tam   = atual->tam - Tam;
            atual->End_i = atual->End_i + Tam;

            organizaBlocoMemAloc();
            return;
        }
        atual = atual->prox;
    }
}

/* Verifica se há espaço de memória disponível.
 * Passa por todos os nós da lista encadeada de memória livre e se esse nó
 * tiver memória suficiente para armazenar o processo, retorna o endereço do
 * nó. Caso contrário retorna -1.                                         */
int buscaEspacoDisp (int Tam)
{
    tipo_MemLivre *atual = inicioMemLivre;

    while (atual) {
        if (atual->tam >= Tam) return atual->End_i;
        atual = atual->prox;
    }
    return -1;
}

/* Organiza Lista de Memória Livre.
 * Ordena a lista de memória livre de acordo com os endereços.
 * Em seguida verifica se é possível agrupar dois blocos em um.
 * Se o endereço inicial de um bloco somado ao tamanho desse bloco
 * foi igual ao endereço incial do bloco seguinte, significa que
 * esses dois blocos podem ser agrupados.                       */
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

/* Finaliza Processo.
 * Começa buscando o processo no nó anterior ao do processo que será finalizado.
 * Ao encontrar, insere um bloco de memória memória livre com o endereço e
 * tamanho do bloco de memória do processo que será finalizado. Em seguida 
 * aponta o nó atual para o nó após ao do bloco que será removido e, finalmente,
 * libera o bloco que será removido.                                          */
void finalizaProcesso(int n)
{
    tipo_MemAloc *atual = inicioMemAloc;

    while (atual) {
        // Caso o primeiro bloco seja o do processo que deve ser finalizado.
        if (atual->NProcesso == n) {
            insereBlocoMemLivre(atual->End_i, atual->tam);
            inicioMemAloc = atual->prox;
            free(atual);
            return;
        }
        // Busca pelo bloco anterior ao do processo que deve ser finalizado.
        if (atual->prox->NProcesso == n) {

            // Inserindo bloco na memória livre.
            insereBlocoMemLivre(atual->prox->End_i, atual->prox->tam);
            
            // Variável temporária para o processo que será removido.
            tipo_MemAloc *apagar = atual->prox;
            
            // Apontando o bloco do processo atual para o bloco
            // seguinte ao do processo sendo finalizado.
            atual->prox = atual->prox->prox;

            free(apagar); // liberando memória do processo finalizado.

            return;
        }
        atual = atual->prox;
    }

    printf("Processo não encontrado");
}

/* Libera Listas
 * Passa em cada nó de cada lista, criando uma variável temporária
 * que armazena o próximo nó livre e libera o nó atual. Em seguida
 * Passa para o próximo nó.                                     */
void liberaLista (void)
{
    tipo_MemLivre *atual_livre = inicioMemLivre;
    tipo_MemLivre *proximo_livre = inicioMemLivre;
    tipo_MemAloc *atual_aloc = inicioMemAloc;
    tipo_MemAloc *proximo_aloc = inicioMemAloc;

    // Liberando a lista de memória livre
    while (atual_livre) {
        proximo_livre = atual_livre->prox;
        free(atual_livre);
        atual_livre = proximo_livre;
    }

    // Liberando a lista de memória alocada.
    while (atual_aloc) {
        proximo_aloc = atual_aloc->prox;
        free(atual_aloc);
        atual_aloc = proximo_aloc;
    }

    inicioMemLivre = NULL;
    inicioMemAloc = NULL;
}

/*                      Funções Extras e Auxiliares                           */

/* Mínimo bloco suficiente
 * Função utilizada para retornar o endereço do menor bloco de memória
 * suficiente para o processo. Busca por e retorna o bloco com memória
 * suficiente para armazenar o processo que seja menor que o primeiro
 * bloco encontrado com memória suficiente para armazenar o processo. */
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

/* Merge para ordenar a Lista de Memória Livre por endereço */
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

/* Merge Sort para ordenar a Lista de Memória Livre por endereço*/
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

/* Merge para ordenar a Lista de Memória Alocada por endereço */
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

/* Merge Sort para ordenar a Lista de Memória Alocada por endereço */
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

/* Função para ordenar a lista de memória alocada por ordem de endereço */
void organizaBlocoMemAloc()
{
    inicioMemAloc = mergeSort_aloc(inicioMemAloc);
}

/* Verifica se o valor inserido para memória do simulador é maior que zero */
int valida_memoria(int mem)
{
    if (mem <= 0) {
        printf("ERRO: A quantidade de memória deve ser um número inteiro maior que zero.");
        return 0;
    } else {
        return 1;
    }
}

int valida_processo_remover(int n)
{
    tipo_MemAloc *atual = inicioMemAloc;
    while (atual) {
        if (atual->NProcesso == n) {
            return 1;
        }
        atual = atual->prox;
    }
    printf("\nEsse processo não existe.\n");
    return 0;
}

/* Deleta Bloco de Memória Livre
 * Remove um Bloco de Memória Livre quando a memória
 * disponível nesse bloco for igual a zero.*/
void del_bloco_mem_livre()
{
    tipo_MemLivre *atual = inicioMemLivre;

    while (atual) {
        if (atual->tam == 0) {
            inicioMemLivre = atual->prox;
            free(atual);
            return;
        }

        if (atual->prox) {
            if (atual->prox->tam == 0) {
                tipo_MemLivre *apagar = atual->prox;
                atual->prox = atual->prox->prox;
                free(apagar);
                return;
            }
        }
        atual = atual->prox;
    }
    return;
}

/* Funções que eu fiz por diversão. */

int quantaMemoriaLivre () 
{
    tipo_MemLivre *atual = inicioMemLivre;
    int total_livre = 0;
    while (atual) {
        total_livre += atual->tam;
        atual = atual->prox;
    }
    return total_livre;
}

int quantaMemoriaAloc ()
{
    tipo_MemAloc *atual = inicioMemAloc;
    int total_aloc = 0;
    while (atual) {
        total_aloc += atual->tam;
        atual = atual->prox;
    }
    return total_aloc;
}

int exibeProcesso (int n_processo)
{
    tipo_MemAloc *atual = inicioMemAloc;
    while (atual) {
        if (atual->NProcesso == n_processo) {
            printf("Numero do Processo: %d\n", atual->NProcesso);
            printf("Endereço do início do bloco de memória: %d\n", atual->End_i);
            printf("Tamanho do processo: %d\n", atual->tam);
        }
        atual = atual->prox;
    }
}
