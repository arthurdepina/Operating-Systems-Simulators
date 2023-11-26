#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IDNAME 30;
#define PATH 100;

typedef struct Node {
    char id[256];
    char path[1024];
    char tipo;
    struct Node *dir_ant;
    struct Node *prox;
    struct None *filhos;
} Node;

Node* criarNo(const char* id, const char tipo, Node* dir_ant)
{
    Node* novoNo = (Node *) malloc (sizeof(Node));
    if (novoNo) {
        strcpy(novoNo->id, id);
        novoNo->tipo = tipo;
        novoNo->dir_ant = dir_ant;
        novoNo->prox = NULL;
        novoNo->filhos = NULL;
    }
}
