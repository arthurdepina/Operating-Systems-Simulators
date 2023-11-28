#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <dirent.h>


typedef struct Node {
    char id[256];           // nome do diretorio ou arquivo
    char path[1024];        // caminho até esse diretório ou arquivo
    char tipo;              // 'a' para arquivo, 'd' para diretório
    int size;               // tamanho em KB (necessário APENAS para arquivo)
    struct Node *dir_ant;   // diretório anterior
    struct Node *prox;      // próximo arquivo ou diretório
    struct Node *filhos;    // lista de diretórios ou arquivos a partir do corrente
} Node;

// Struct utilizada na implementação de
// fila para imprimir a árvore em largura
typedef struct Queue {
    Node **items;
    int front, rear, size, capacity;
} Queue;


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

Queue* createQueue(int capacity);

int isFull(Queue *queue);

int isEmpty(Queue *queue);

void enqueue(Queue *queue, Node *item);

Node* dequeue(Queue *queue);

Node* encontrarRaiz(Node *atual);

void imprimirLargura(Node *atual);

void mostrar_no(const Node *no);

void mostrar_no(const Node *no);

bool verificaInsercao(Node* atual);

Node* createNode(const char* name, const char* path, char tipo, Node* dir_ant);

void mapDirectory(const char* basePath, Node* parent);

long getFileSize(const char *filename);

void freeTreeFromNode(Node *node);

void freeTree(Node *root);



Node* createNode (const char* name, const char* path, char tipo, Node* dir_ant)
{
    Node* node = (Node*)malloc(sizeof(Node));
    strcpy(node->id, name);
    strcpy(node->path, path);
    node->tipo = tipo;
    node->size = (tipo == 'a') ? getFileSize(path) : 0;
    node->dir_ant = dir_ant;
    node->prox = NULL;
    node->filhos = NULL;
    return node;
}

/* Mapear diretório
 * Recebe um ponteiro para a raiz e passa pelos diretórios e arquivos
 * os adicionando a árvore.                                         */
void mapDirectory (const char* basePath, Node* parent)
{
    char path[1024];
    struct dirent *dp;
    DIR *dir = opendir(basePath);

    if (!dir)
        return; // Não foi possível abrir o diretório.

    Node* lastChild = NULL;

    while ((dp = readdir(dir)) != NULL) {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {
            sprintf(path, "%s/%s", basePath, dp->d_name);

            struct stat statbuf;
            if (stat(path, &statbuf) != 0)
                continue; // Erro ao obter informações do arquivo/diretório.

            char tipo = S_ISDIR(statbuf.st_mode) ? 'd' : 'a';
            Node* newNode = createNode(dp->d_name, path, tipo, parent);

            if (tipo == 'd') {
                // Mapear subdiretório.
                mapDirectory(path, newNode);
            }

            if (lastChild == NULL) {
                parent->filhos = newNode;
            } else {
                lastChild->prox = newNode;
            }
            lastChild = newNode;
        }
    }

    closedir(dir);
}

/* Retorna tamanho de um arquivo.
 * Recebe nome do arquivo e retorna esse nome                       */
long getFileSize (const char *filename)
{
    struct stat st;

    if (stat(filename, &st) == 0) {
        return st.st_size; // Retorna o tamanho do arquivo em bytes.
    } else {
        perror("Erro ao obter o tamanho do arquivo");
        return -1; // Retorna -1 em caso de erro.
    }
}

/* Cria raiz
 * Cria ponteiro para o nó com a raiz e retorna esse ponteiro   */
Node* criarRaiz (const char *id)
{
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

/* Inserir Arquivo
 * Recebe ponteiro do nó para o diretório atual, nome e tamanho
 * do arquivo a ser criado e cria um nó para o arquivo nesse diretório.
 * Retorna true se bem sucedido, false caso contrário                   */
bool inserirArquivo (Node* atual, const char* nome, int size)
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

/* Inserir diretório
 * Recebe ponteiro para nó atual e nome do diretório a ser criado.
 * Cria esse diretório no diretório passado no nó atual.
 * Retorna true se bem sucedido                                 */
bool inserirDiretorio (Node* atual, const char* nome)
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

/* Mudar de Arquivo ou Diretório
 * Recebe ponteiro para o nó (arquivo ou diretório) atual e
 * caminho para o nó (arquivo ou diretório) onde queremos ir.
 * Sobe até a raiz e procura esse nó usando buscarNo            */
Node* changeNode (Node* atual, const char* nome)
{   // nome: caminho para o nó destino
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

/* Busca nó 
 * Recebe ponteiro para o nó atual e na variável 'nome' o
 * caminho para o nó que estamos procurando. Sobe até a raiz
 * Funciona recursivamente procurando entre os filhos.
 * Retorna NULL ou ponteiro para o nó que está sendo buscado.   */
Node* buscarNo (Node* no, const char* nome)
{
    if (no == NULL) {
        return NULL;
    }

    // Verifica se o nó atual é o que estamos procurando
    if (strcmp(no->path, nome) == 0) {
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

/*                    Funções usadas para deletar arquivo                       */
/********************************************************************************/
/* Deletar Arquivo
 * Recebe ponteiro para nó atual e em 'nome' recebe o path para o arquivo que
 * queremos deletar.
 * Sobe até a raiz a partir do nó atual e utiliza encontraArquivo para
 * encontrar o arquivo que queremos deletar. Em seguida libera a memória
 * utilizada por esse arquivo e faz com que o pai pare de apontar para ele.     */
Node* deletaArquivo (Node* atual, const char* nome)
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

/* Encontrar arquivo (para que que este seja deletado)
 * Recebe nó para raiz e recursivamente procura nos filhos para
 * encontrar o nó que devemos deletar. Retorna ponteiro para esse
 * nó se for encontrado e NULL caso contrário.
 * Para encontrar o nó que queremos deletar, comparamos o caminho
 * passado como caminho do nó em que estamos.                                   */
Node* encontraArquivo (Node** pai, Node* no, const char* nome)
{
    if (no == NULL) {
        return NULL;
    }

    // Procurar o arquivo nos filhos do nó atual
    Node* temp = no->filhos;
    while (temp != NULL) {
        if (temp->tipo == 'a' && strcmp(temp->path, nome) == 0) {
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

/*                                  Fim                                        */
/*******************************************************************************/

/*                    Funções usadas para deletar arquivo                       */
/********************************************************************************/

/* Essa função não foi pedida na proposta do projeto, é uma função extra.
 * Ainda há um problema na hora de redefinir o path dos arquivos e diretórios
 * filhos. Além disso, ainda estamos procurando o diretório por nome e não
 * por path.                                                                    */
Node* deletaDiretorio (Node* atual, const char* nomeDoDiretorio)
{
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

Node* encontraDiretorio (Node** pai, Node* no, const char* nome)
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

/*                                  Fim                                        */
/*******************************************************************************/

/* Imprimir profundidade
 * Recebe nó atual e a partir desse nó sobe até a raiz.
 * Em seguida desce a árvore recursivamente imprimindo os nós.  */
void imprimirProfundidade (Node* no)
{
    // Encontrar a raiz da árvore
    Node* raiz = no;
    while (raiz != NULL && raiz->dir_ant != NULL) {
        raiz = raiz->dir_ant;
    }
 
    // Chamar a função auxiliar para imprimir a árvore
    imprimirProfundidadeRecursiva(raiz);
}

void imprimirProfundidadeRecursiva (Node* no)
{
    if (no == NULL) return;

    // Imprimir o ID do nó
    if (no->tipo == 'd') { 
        printf("%s\n", no->id); 
    } else {
        printf("%s %d bytes\n", no->id, no->size);
    }

    // Chamar recursivamente para todos os filhos
    Node* temp = no->filhos;
    while (temp != NULL) {
        imprimirProfundidadeRecursiva(temp);
        temp = temp->prox;
    }
}

/********************************************************************************/
/*                              Imprimir em Largura                             */

/* As funções a seguir são utilizadas para imprimir a árvore em largura.
 * Para isso, coloco os nós em uma fila e depois imprimo essa fila.
 * Por isso, foi necessário implementar uma fila primeiro.                      */


// Função auxiliar para criar uma nova fila

Queue* createQueue (int capacity)
{
    Queue *queue = (Queue*)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->items = (Node**)malloc(queue->capacity * sizeof(Node*));
    return queue;
}

int isFull (Queue *queue)
{
    return (queue->size == queue->capacity);
}

int isEmpty (Queue *queue)
{
    return (queue->size == 0);
}

void enqueue (Queue *queue, Node *item)
{
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->items[queue->rear] = item;
    queue->size = queue->size + 1;
}

Node* dequeue (Queue *queue)
{
    if (isEmpty(queue))
        return NULL;
    Node *item = queue->items[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

// Função para encontrar a raiz da árvore
Node* encontrarRaiz (Node *atual)
{
    while (atual != NULL && atual->dir_ant != NULL) {
        atual = atual->dir_ant;
    }
    return atual;
}

// Função para imprimir a árvore em largura
void imprimirLargura (Node *atual)
{
    if (atual == NULL) return;

    atual = encontrarRaiz(atual);  // Encontrar a raiz da árvore

    Queue *queue = createQueue(100);  // Supondo que 100 é um tamanho suficiente para a fila
    enqueue(queue, atual);

    while (!isEmpty(queue)) {
        Node *current = dequeue(queue);

        // Imprimir o nó atual
        if (current->tipo == 'd') {
            printf("%s\n", current->path);
        } else {
            printf("%s %d bytes\n", current->path, current->size);
        }

        // Adicionar todos os filhos do nó atual na fila
        Node *child = current->filhos;
        while (child) {
            enqueue(queue, child);
            child = child->prox;
        }
    }

    free(queue->items);
    free(queue);
}
/*                                  Fim                                        */
/*******************************************************************************/

/*******************************************************************************/
/*                            Funções Extras                                    */

void mostrar_no (const Node *no)
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
bool verificaInsercao (Node* atual)
{
    if (atual == NULL) {
        return false; // Retorna false se o nó atual for NULL
    }
    return atual->tipo == 'd'; // Retorna true se for um diretório
}

void freeTree (Node *root)
{
    if (root == NULL) return;

    // Libera recursivamente todos os filhos
    Node *child = root->filhos;
    while (child != NULL) {
        Node *nextChild = child->prox;
        freeTree(child); // Chama a função recursivamente para o filho
        child = nextChild;
    }

    // Libera o nó atual
    free(root);
}

void freeTreeFromNode (Node *node)
{
    if (node == NULL) return;

    // Encontrar a raiz da árvore
    Node *root = node;
    while (root->dir_ant != NULL) {
        root = root->dir_ant;
    }

    // Começa a liberação da árvore a partir da raiz encontrada
    freeTree(root);
}

/*                                  Fim                                        */
/*******************************************************************************/
