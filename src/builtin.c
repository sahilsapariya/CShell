#include <stdio.h>
#include <stdlib.h>
#include "builtin.h"

void print_prompt() {
    printf(PROMPT_MSG);
}

void exit_shell() {
    char user_input;
    printf("\nLeaving early? Are you sure you want to exit? (y/N)\n");
    scanf("%c", &user_input);

    if (user_input == 'y') {
        printf("Exiting shell...\n");
        exit(0);
    }
}

void read_input(char *input) {
    fgets(input, 1024, stdin);
    return;
}

void display_output(char *output) {
    printf("%s", output);
    return;
}