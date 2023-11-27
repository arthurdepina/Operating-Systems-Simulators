#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "n-AryTree.c"
#include "auxiliares.c"

int main() {
    Node *atual = malloc(sizeof(Node));

    char root_name[100];
    printf("Nome da Raiz?\n");
    printf("> ");
    fgets(root_name, sizeof(root_name), stdin);
    root_name[strcspn(root_name, "\n")] = 0; // remove o caractere de nova linha
    
    atual = criarRaiz(root_name);
    printf("Nome da raiz definido como: %s\n", root_name);

    show_commands();

    while (true) {
        char input[100];
        char comando, tipo;
        char nome[50];
        int tamanho = 0;

        printf("> ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0; // Removing the newline character that fgets reads

        switch (input[0]) {
                                        // Criar arquivo ou diretório
            case 'm':

                if (input[2] == 'd') {
                    if (!getting_input(input, &comando, &tipo, nome)) { fail(); break; }
                } else {
                    if (!getting_input_with_size(input, &comando, &tipo, nome, &tamanho)) { fail(); break; }
                }
                if (tipo == 'd') {
                    inserirDiretorio(atual, nome);
                } else if (tipo == 'a') {
                    inserirArquivo(atual, nome, tamanho);
                } else {
                    fail();
                    break;
                }
                break;

                                        // Mudar de diretório ou arquivo
            case 'c':

                if (!getting_input(input, &comando, &tipo, nome)) { fail(); break; }
                atual = changeNode(atual, nome);
                break;

                                        // Deletar diretório ou arquivo
            case 'd':

                if (!getting_input(input, &comando, &tipo, nome)) { fail(); break; }
                if (tamanho) printf("TAMANHO: %d\n", tamanho);
                printf("\n");
                if (tipo == 'd') {
                    alteraPaths(atual, nome);
                    atual = deletaDiretorio(atual, nome);
                } else if (tipo == 'a') {
                    atual = deletaArquivo(atual, nome);
                } else {
                    fail();
                    break;
                }
                break;

                                        // Exibir árvore em profundidade
            case 'p':

                // profundidade
                imprimirProfundidade(atual);
                break;

                                        // Exibir árvore em largura
            case 'l':

                // largura
                break;

            case '-':

                if (!strcmp(input, "--end")) {
                    printf("\nPrograma finalizado.\n\n");
                    return 0;
                } else if (!strcmp(input, "--help")) {
                    show_commands();
                } else if (!strcmp(input, "--show")) {
                    mostrar_no(atual);
                }
                break;

            default:
                printf("Input invalido");
                break;
        }
    }
    return 0;
}

                // printf("\n");
                // printf("COMANDO: %c\n", comando);
                // printf("TIPO: %c\n", tipo);
                // printf("NOME: %s\n", nome);
                // if (tamanho) printf("TAMANHO: %d\n", tamanho);
                // printf("\n");

/*          
 *                  Problemas conhecidos:
 * Não podem haver dois nós com mesmo id (nome)
 *      Na verdade, acho que talvez isso seja um problema apenas quando
 *      queremos deletar ou mudar para algum node. Nesses casos será
 *      necessário passar o path para esses nodes.
 * Quando removemos um diretorio, o path dos filhos nao é alterado.
 *      Talvez compense usar listas nos paths. Não vou perder tempo
 *      com isso por agora porque o enunciado nao pede para deletar
 *      diretórios.
*/
