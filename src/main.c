#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include "builtin.h"

int main() {
    char cwd[1024];
    getlogin_r(cwd, sizeof(cwd));

    do {
        print_prompt();
        read_input(cwd);

        // check if user wants to exit
        if (strcmp(cwd, "exit\n") == 0) {
            exit_shell();
        }

        display_output(cwd);
    } while (1);

    return 0;
}