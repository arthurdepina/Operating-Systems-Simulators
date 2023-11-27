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


Node* criarRaiz(const char *id);
void imprimirProfundidadeRecursiva(Node* no);
bool inserirArquivo(Node* atual, const char* nome, int size);
bool inserirDiretorio(Node* atual, const char* nome);
Node* changeNode(Node* atual, const char* nome);
Node* buscarNo(Node* no, const char* nome);
Node* deletaArquivo(Node* atual, const char* nome);
Node* encontraArquivo(Node** pai, Node* no, const char* nome);
Node* deletaDiretorio(Node* atual, const char* nomeDoDiretorio);
Node* encontraDiretorio(Node** pai, Node* no, const char* nome);
void alteraPaths();
void atualizaPathsFilhos();
void imprimirProfundidade(Node* no);
void imprimirProfundidadeRecursiva(Node* no);
void mostrar_no(const Node *no);
bool verificaInsercao(Node* atual);


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

bool inserirArquivo(Node* atual, const char* nome, int size)
{
    if (!verificaInsercao(atual)) return false;

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

    return true;
}

bool inserirDiretorio(Node* atual, const char* nome)
{
    if (!verificaInsercao(atual)) return false;
    Node* novoNo = (Node*)malloc(sizeof(Node));
    strcpy(novoNo->id, nome);
    snprintf(novoNo->path, sizeof(novoNo->path), "%s/%s", atual->path, nome);
    novoNo->size = 0;
    novoNo->tipo = 'd';
    novoNo->dir_ant = atual;
    novoNo->prox = NULL;
    novoNo->filhos = NULL;

    if (atual->filhos == NULL) {
        atual->filhos = novoNo;
    } else {
        Node* temp = atual->filhos;
        while (temp->prox != NULL) {
            temp = temp->prox;
        }
        temp->prox = novoNo;
    }
    return true;
}

Node* changeNode(Node* atual, const char* nome)
{
    if (atual == NULL || nome == NULL) {
        return NULL; // Retorna NULL se o nó atual ou o nome for NULL
    }

    // Subir até a raiz da árvore
    Node* raiz = atual;
    while (raiz->dir_ant != NULL) {
        raiz = raiz->dir_ant;
    }

    // Chamar a função de busca a partir da raiz
    return buscarNo(raiz, nome);
}

Node* buscarNo(Node* no, const char* nome)
{
    if (no == NULL) {
        return NULL;
    }

    // Verifica se o nó atual é o que estamos procurando
    if (strcmp(no->id, nome) == 0) {
        return no;
    }

    // Procura nos filhos do nó atual
    Node* temp = no->filhos;
    while (temp != NULL) {
        Node* encontrado = buscarNo(temp, nome);
        if (encontrado != NULL) {
            return encontrado;
        }
        temp = temp->prox;
    }

    return NULL; // Retorna NULL se o nó não for encontrado
}

Node* deletaArquivo(Node* atual, const char* nome)
{
    if (atual == NULL || nome == NULL) {
        return NULL; // Retorna NULL se o nó atual ou o nome for NULL
    }

    // Subir até a raiz da árvore
    Node* raiz = atual;
    while (raiz->dir_ant != NULL) {
        raiz = raiz->dir_ant;
    }

    // Procurar o arquivo a partir da raiz e obter o pai
    Node* pai = NULL;
    Node* arquivo = encontraArquivo(&pai, raiz, nome);

    // Se o arquivo não for encontrado, retorna NULL
    if (arquivo == NULL) {
        return NULL;
    }

    // Se o arquivo a ser deletado é o atual, ajustar o atual para o pai
    Node* novoAtual = (arquivo == atual) ? pai : atual;

    // Remover o arquivo da lista de filhos do pai
    if (pai != NULL) {
        if (pai->filhos == arquivo) {
            pai->filhos = arquivo->prox;
        } else {
            Node* temp = pai->filhos;
            while (temp != NULL && temp->prox != arquivo) {
                temp = temp->prox;
            }
            if (temp != NULL) {
                temp->prox = arquivo->prox;
            }
        }
    }

    free(arquivo); // Liberar a memória do nó do arquivo
    return novoAtual;
}

Node* encontraArquivo(Node** pai, Node* no, const char* nome)
{
    if (no == NULL) {
        return NULL;
    }

    // Procurar o arquivo nos filhos do nó atual
    Node* temp = no->filhos;
    while (temp != NULL) {
        if (temp->tipo == 'a' && strcmp(temp->id, nome) == 0) {
            *pai = no; // Configurar o pai do arquivo encontrado
            return temp;
        }
        Node* arquivo = encontraArquivo(pai, temp, nome);
        if (arquivo != NULL) {
            return arquivo;
        }
        temp = temp->prox;
    }

    return NULL; // Retorna NULL se o arquivo não for encontrado
}

Node* deletaDiretorio(Node* atual, const char* nomeDoDiretorio) {
    if (atual == NULL || nomeDoDiretorio == NULL) {
        return NULL; // Retorna NULL se o nó atual ou o nome do diretório for NULL
    }

    // Subir até a raiz da árvore
    Node* raiz = atual;
    while (raiz->dir_ant != NULL) {
        raiz = raiz->dir_ant;
    }

    // Procurar o diretório a partir da raiz e obter o pai
    Node* pai = NULL;
    Node* diretorio = encontraDiretorio(&pai, raiz, nomeDoDiretorio);

    // Se o diretório não for encontrado, retorna NULL
    if (diretorio == NULL) {
        return NULL;
    }

    // Se o diretório a ser deletado é o atual, ajustar o atual para o pai
    Node* novoAtual = (diretorio == atual) ? pai : atual;

    // Lidar com os filhos do diretório
    if (diretorio->filhos != NULL) {
        // Se o diretório a ser deletado tem filhos, reatribuí-los para o pai
        if (pai != NULL) {
            // Encontrar o último filho do pai
            Node* ultimoFilhoPai = pai->filhos;
            while (ultimoFilhoPai->prox != NULL) {
                ultimoFilhoPai = ultimoFilhoPai->prox;
            }
            ultimoFilhoPai->prox = diretorio->filhos;
        } else {
            // Se o diretório não tem pai, então é a raiz e não pode ser deletado
            return atual;
        }
    }

    // Remover o diretório da lista de filhos do pai
    if (pai->filhos == diretorio) {
        pai->filhos = diretorio->prox;
    } else {
        Node* temp = pai->filhos;
        while (temp != NULL && temp->prox != diretorio) {
            temp = temp->prox;
        }
        if (temp != NULL) {
            temp->prox = diretorio->prox;
        }
    }

    free(diretorio); // Liberar a memória do nó do diretório
    return novoAtual;
}

Node* encontraDiretorio(Node** pai, Node* no, const char* nome)
{
    if (no == NULL) {
        return NULL;
    }

    // Procurar o diretório nos filhos do nó atual
    Node* temp = no->filhos;
    while (temp != NULL) {
        if (temp->tipo == 'd' && strcmp(temp->id, nome) == 0) {
            *pai = no; // Configurar o pai do diretório encontrado
            return temp;
        }
        Node* diretorio = encontraDiretorio(pai, temp, nome);
        if (diretorio != NULL) {
            return diretorio;
        }
        temp = temp->prox;
    }

    return NULL; // Retorna NULL se o diretório não for encontrado
}

void alteraPaths ()
{
    
}

void atualizaPathsFilhos ()
{
    
}

void imprimirProfundidade(Node* no)
{
    // Encontrar a raiz da árvore
    Node* raiz = no;
    while (raiz != NULL && raiz->dir_ant != NULL) {
        raiz = raiz->dir_ant;
    }

    // Chamar a função auxiliar para imprimir a árvore
    imprimirProfundidadeRecursiva(raiz);
}

void imprimirProfundidadeRecursiva(Node* no)
{
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

void mostrar_no(const Node *no)
{
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


// Verifica se estamos tentando inserir em um diretorio
bool verificaInsercao(Node* atual)
{
    if (atual == NULL) {
        return false; // Retorna false se o nó atual for NULL
    }
    return atual->tipo == 'd'; // Retorna true se for um diretório
}
