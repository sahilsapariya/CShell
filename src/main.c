#include <stdio.h>
#include <string.h>
#include "builtin.h"

int main() {
    initialize_shell();
    char input[1024];

    // Infinite loop to keep the shell running
    do {
        print_prompt();
        read_input(input);

        // Check if user wants to exit
        if (strcmp(input, "exit") == 0) {
            exit_shell();
        } else {
            execute_command(input);  // Execute commands
        }
    } while (1);

    return 0;
}
