#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/****************************************************************
 * Essas são funções utilizadas para receber input do usuário.
 * Criei elas porque queria permitir que diretórios e arquivo
 * possuíssem espaços no nome.
 ****************************************************************/

int getting_input(char *input, char *firstLetter, char *secondLetter, char *name)
{
    // Parse the input
    if (sscanf(input, "%c %c %[^\n]", firstLetter, secondLetter, name) == 3) {
        return 1; // Return 1 for success
    } else {
        return 0; // Return 0 for failure
    }
}

int getting_input_with_size(const char *input, char *letter, char *type, char *name, int *size)
{
    // Read the first two characters
    if (sscanf(input, "%c %c", letter, type) != 2) {
        return 0; // Return 0 for failure
    }

    // Find the position of the last space (before the size)
    const char *last_space = strrchr(input, ' ');
    if (!last_space || sscanf(last_space + 1, "%d", size) != 1) {
        return 0; // Return 0 for failure
    }

    // Calculate the length of the name part and copy it
    int name_length = last_space - input - 4; // Subtract positions of letter, type, and spaces
    if (name_length <= 0 || name_length >= 150) {
        return 0; // Return 0 for failure
    }
    strncpy(name, input + 4, name_length);
    name[name_length] = '\0'; // Null-terminate the name string

    return 1; // Return 1 for success
}

void fail ()
{
    printf("\nERRO\n\n");
}

void show_commands ()
{
    printf("\nm <a/d> <nome> <tamanho (se for ) : criar dir ou arq\n");
    printf("c <a/d> <path do diretorio> : mudar repositorio\n");
    printf("d <a/d> <path do arquivo> : deletar arquivo\n");
    printf("p : arvore em profundidade\n");
    printf("l : arvore em largura\n");
    printf("--help : mostrar comandos\n");
    printf("--end : encerrar\n");
    printf("--show : mostrar no atual\n");
    printf("\n");
}