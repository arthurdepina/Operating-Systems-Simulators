#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "n-AryTree.c"
#include "auxiliares.c"

#define IDNAME 30;
#define PATH 100;

int main ()
{
    printf("m <a/d> <nome> <tamanho (se for ) -- criar dir ou arq\nc <a/d> <nome do diretorio> -- mudar repositorio\nd <a/d> <nome do arquivo> -- deletar arquivo\np -- arvore em profundidade\nl -- arvore em largura\n");
    while (true)
    {
        char input[100];
        char comando, tipo;
        char nome[50];
        int tamanho = 0;

        printf("> ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0; // Removing the newline character that fgets reads

        if (input[0] == 'm') {
            char *a_d = &input[2];
            if (!strcmp(a_d, "d")) {
                getting_input_diretorio(input, &comando, &tipo, nome);
            } else {
                getting_input_arquivo(input, &comando, &tipo, nome, &tamanho);
            }
            printf("COMANDO: %c\n", comando);
            printf("TIPO: %c\n", tipo);
            printf("NOME: %s\n", nome);
            if (tamanho) printf("TAMANHO: %d\n", tamanho);
        }

        if (!strcmp(input, "--end")) break;
    }
    return 0;
}