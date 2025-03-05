#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "builtin.h"

#define MAX_COMMAND_LEX 1024

void read_input(char *input) {
    if (fgets(input, MAX_COMMAND_LEX, stdin) == NULL) {
        perror("Error reading input");
        exit(EXIT_FAILURE);
    }
    input[strcspn(input, "\n")] = 0;  // Remove newline
}

char **tokenize_input(char *input) {
    char **tokens = malloc(1024 * sizeof(char *));
    if (tokens == NULL) {
        fprintf(stderr, "error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    char *token;
    int i = 0;

    token = strtok(input, " \n");
    while (token != NULL) {
        tokens[i] = token;
        i++;
        if (i >= 1024) {
            fprintf(stderr, "error: Too many tokens\n");
            free(tokens);
            exit(EXIT_FAILURE);
        }
        token = strtok(NULL, " \n");
    }

    tokens[i] = NULL;
    return tokens;
}

void exit_shell() {
    char user_input;
    printf("Leaving early? Are you sure you want to exit? (y/N)\n");
    int result = scanf("%c", &user_input);

    // Clear input buffer
    while (getchar() != '\n');

    if (result != 1) {
        fprintf(stderr, "error: Error reading input\n");
        return;
    }

    if (user_input == 'y' || user_input == 'Y') {
        printf("Exiting shell...\n");
        exit(0);
    } else {
        printf("Continuing shell...\n");
    }
}
