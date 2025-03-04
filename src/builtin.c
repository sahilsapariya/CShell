#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "builtin.h"

void initialize_shell() {
    char cwd[1024];
    char *username;
    char logged_in_username[1024];

    // get the current login username
    getlogin_r(logged_in_username, sizeof(logged_in_username));

    // get the current working directory
    getcwd(cwd, sizeof(cwd));

    // get the username
    username = getenv("USER");

    // initialize the program
    printf("Welcome to cshell, %s@%s\n", username, logged_in_username);
    printf("Type 'exit' to leave the shell\n");
    printf("Current working directory: %s\n", cwd);
    printf("\n");
}

void print_prompt() {
    printf(PROMPT_MSG);
}

void read_input(char *input) {
    fgets(input, 1024, stdin);
    return;
}

void display_output(char **output) {
    for (int i = 0; output[i] != NULL; i++) {
        printf("%s\n", output[i]);
    }
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
    printf("\nLeaving early? Are you sure you want to exit? (y/N)\n");
    scanf("%c", &user_input);

    // Clear new line character left in input buffer,
    // it prevents the printing 2 times the prompt message
    while (getchar() != '\n');

    if (user_input == 'y') {
        printf("Exiting shell...\n");
        exit(0);
    }
}