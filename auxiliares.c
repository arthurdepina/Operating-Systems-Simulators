#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getting_input_diretorio(char *input, char *firstLetter, char *secondLetter, char *name) {
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