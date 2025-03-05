#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "builtin.h"

#define MAX_COMMAND_LEX 1024

void read_input(char *input) {
    fgets(input, MAX_COMMAND_LEX, stdin);
    input[strcspn(input, "\n")] = 0;  // Remove newline
}

char **tokenize_input(char *input) {
    char **tokens = malloc(1024 * sizeof(char *));
    char *token;
    int i = 0;

    token = strtok(input, " \n");
    while (token != NULL) {
        tokens[i] = token;
        i++;
        token = strtok(NULL, " \n");
    }

    tokens[i] = NULL;
    return tokens;
}

void exit_shell() {
    char user_input;
    printf("Leaving early? Are you sure you want to exit? (y/N)\n");
    scanf("%c", &user_input);

    // Clear input buffer
    while (getchar() != '\n');

    if (user_input == 'y' || user_input == 'Y') {
        printf("Exiting shell...\n");
        exit(0);
    }
}
