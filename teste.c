#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int getting_input_diretorio(char *input, char *firstLetter, char *secondLetter, char *name) {
    printf("WHAAAT");
    // Parse the input
    if (sscanf(input, "%c %c %[^\n]", firstLetter, secondLetter, name) == 3) {
        // Successfully parsed the input
        printf("First letter: %c, Second letter: %c, Name: %s\n", *firstLetter, *secondLetter, name);

        // Example action based on the first letter
        if (*firstLetter == 'm') {
            printf("Change to: %s\n", name);
        }
        return 1; // Return 1 for success
    } else {
        printf("Invalid input format.\n");
        return 0; // Return 0 for failure
    }
}

int getting_input_arquivo(const char *input, char *letter, char *type, char *name, int *size) {
    // Assuming input is already trimmed of the newline

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
            char *a_d = input[2];
            printf("a_d = %c\n", a_d);
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