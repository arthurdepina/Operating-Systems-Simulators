#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "n-AryTree.c"
#include "auxiliares.c"

int main() {
    printf("m <a/d> <nome> <tamanho (se for ) -- criar dir ou arq\nc <a/d> <nome do diretorio> -- mudar repositorio\nd <a/d> <nome do arquivo> -- deletar arquivo\np -- arvore em profundidade\nl -- arvore em largura\n\n");
    while (true) {
        char input[100];
        char comando, tipo;
        char nome[50];
        int tamanho = 0;

        printf("> ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0; // Removing the newline character that fgets reads

        switch (input[0]) {
            case 'm':
                if (input[2] == 'd') {
                    if (!getting_input_diretorio(input, &comando, &tipo, nome)) { fail(); break; }
                } else {
                    if (!getting_input_arquivo(input, &comando, &tipo, nome, &tamanho)) { fail(); break; }
                }
                printf("\n");
                printf("COMANDO: %c\n", comando);
                printf("TIPO: %c\n", tipo);
                printf("NOME: %s\n", nome);
                if (tamanho) printf("TAMANHO: %d\n", tamanho);
                printf("\n");
                if (tipo == 'd') {
                    // Criar Diretorio
                } else if (tipo == 'a') {
                    // Criar arquivo
                } else {
                    fail();
                    break;
                }
                break;

            case 'd':
                // deletar arquivo
                break;

            case 'p':
                // profundidade
                break;

            case 'l':
                // largura
                break;

            case '-':
                if (!strcmp(input, "--end")) {
                    return 0;
                }
                break;

            default:
                printf("Input invalido");
                break;
        }
    }
    return 0;
}
