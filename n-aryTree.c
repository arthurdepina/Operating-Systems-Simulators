#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Node {
    char id[256];
    char path[1024];
    char tipo;
    int size;
    struct Node *dir_ant;
    struct Node *prox;
    struct Node *filhos;
} Node;


void imprimirProfundidadeRecursiva(Node* no);

Node* criarRaiz(const char *id) {
    Node *raiz = malloc(sizeof(Node));
    if (raiz == NULL) {
        printf("Erro ao alocar memória para a raiz\n");
        return NULL;
    }

    strncpy(raiz->id, id, sizeof(raiz->id));
    raiz->id[sizeof(raiz->id) - 1] = '\0'; // Garantir terminação da string

    strcpy(raiz->path, ""); // Se necessário, ajuste o path da raiz
    strcat(raiz->path, id);

    raiz->tipo = 'd'; // Tipo 'd' para diretório
    raiz->dir_ant = NULL; // Sem diretório anterior
    raiz->prox = NULL; // Sem próximo
    raiz->filhos = NULL; // Sem filhos

    return raiz;
}

Node* inserirArquivo(Node* atual, const char* nome, int size) {
    Node* novoNo = (Node*)malloc(sizeof(Node));
    strcpy(novoNo->id, nome);
    snprintf(novoNo->path, sizeof(novoNo->path), "%s/%s", atual->path, nome);
    novoNo->size = size;
    novoNo->tipo = 'a';
    novoNo->dir_ant = atual;
    novoNo->prox = NULL;
    novoNo->filhos = NULL;

    // Inserir no final da lista de filhos do nó atual
    if (atual->filhos == NULL) {
        atual->filhos = novoNo;
    } else {
        Node* temp = atual->filhos;
        while (temp->prox != NULL) {
            temp = temp->prox;
        }
        temp->prox = novoNo;
    }

    return novoNo;
}

void imprimirProfundidade(Node* no) {
    // Encontrar a raiz da árvore
    Node* raiz = no;
    while (raiz != NULL && raiz->dir_ant != NULL) {
        raiz = raiz->dir_ant;
    }

    // Chamar a função auxiliar para imprimir a árvore
    imprimirProfundidadeRecursiva(raiz);
}

void imprimirProfundidadeRecursiva(Node* no) {
    if (no == NULL) return;

    // Imprimir o ID do nó
    printf("%s\n", no->path);

    // Chamar recursivamente para todos os filhos
    Node* temp = no->filhos;
    while (temp != NULL) {
        imprimirProfundidadeRecursiva(temp);
        temp = temp->prox;
    }
}

void mostrar_no(const Node *no) {
    printf("\n");
    if (no == NULL) {
        printf("Nó nulo\n");
        return;
    }

    printf("ID: %s\n", no->id);
    printf("Caminho: %s\n", no->path);
    printf("Tipo: %c\n", no->tipo);

    // Se desejar, também pode imprimir informações sobre os ponteiros, como:
    printf("Diretorio anterior: %p\n", (void *)no->dir_ant);
    printf("Proximo no: %p\n", (void *)no->prox);
    printf("Primeiro filho: %p\n", (void *)no->filhos);
    printf("\n");
}
