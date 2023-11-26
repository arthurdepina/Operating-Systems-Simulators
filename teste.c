#include <stdio.h>
#include <string.h>

int getting_input(const char *input, char *letter, char *type, char *name, int *size) {
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

int main() {
    char input[200];
    char letter, type;
    char name[150];
    int size;

    printf("Enter input (format: <letter> <type> <name> <size>): ");
    fgets(input, sizeof(input), stdin);

    // Remove newline character at the end if present
    input[strcspn(input, "\n")] = 0;

    if (getting_input(input, &letter, &type, name, &size)) {
        printf("Letter: %c\n", letter);
        printf("Type: %c\n", type);
        printf("Name: %s\n", name);
        printf("Size: %d\n", size);
    } else {
        printf("Invalid input format.\n");
    }

    return 0;
}
