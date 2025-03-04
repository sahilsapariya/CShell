#include <stdio.h>
#include <stdlib.h>
#include "builtin.h"

void print_prompt() {
    printf(PROMPT_MSG);
}

void read_input(char *input) {
    fgets(input, 1024, stdin);
    return;
}

void display_output(char *output) {
    printf("%s", output);
    return;
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