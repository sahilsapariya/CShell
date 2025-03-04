#include<stdio.h>
#include<string.h>
#include "builtin.h"

int main() {
    initialize_shell();

    char input[1024];

    // infinite loop to keep the shell running
    do {
        print_prompt();
        read_input(input);

        // check if user wants to exit
        if (strcmp(input, "exit\n") == 0) {
            exit_shell();
        }

        // tokenize the input
        char **tokens = tokenize_input(input);


        display_output(tokens);
    } while (1);

    return 0;
}