#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <libgen.h>
#include "builtin.h"

#define PROMPT_MSG "cshell=# "
#define MAX_COMMAND_LEX 1024
#define MAX_ARGS 100

char cwd[1024];
char *username;

void initialize_shell() {
    char logged_in_username[1024];

    // Get current login username
    if (getlogin_r(logged_in_username, sizeof(logged_in_username)) != 0) {
        perror("Error getting login username");
        exit(EXIT_FAILURE);
    }

    // Get current working directory
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("Error getting current working directory");
        exit(EXIT_FAILURE);
    }

    // Get the username from environment
    username = getenv("USER");
    if (username == NULL) {
        fprintf(stderr, "error: Error retrieving USER environment variable\n");
        exit(EXIT_FAILURE);
    }

    // Welcome message
    printf("Welcome to cshell, %s@%s\n", username, logged_in_username);
    printf("Type 'exit' to leave the shell\n");
    printf("Current working directory: %s\n", cwd);
    printf("\n");
}

void print_prompt() {
    printf("%s @ %s =# ", username, basename(cwd));
}

void execute_command(char *input) {
    char *args[MAX_ARGS];
    char *token;
    int i = 0;

    // Tokenize the input
    token = strtok(input, " ");
    while (token != NULL && i < MAX_ARGS - 1) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;

    // Check if the input is empty
    if (args[0] == NULL) {
        return;  // No command entered
    }

    // Handle built-in commands
    if (strcmp(args[0], "exit") == 0) {
        exit_shell();
    } else if (strcmp(args[0], "cd") == 0) {
        if (args[1] == NULL) {
            fprintf(stderr, "cshell: expected argument to \"cd\"\n");
        } else {
            if (chdir(args[1]) != 0) {
                perror("cshell");
            } else {
                if (getcwd(cwd, sizeof(cwd)) == NULL) {
                    perror("Error getting current working directory");
                }
            }
        }
        return;
    }

    // Fork and execute external commands
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        if (execvp(args[0], args) == -1) {
            perror("cshell");
            exit(EXIT_FAILURE);
        }
    } else {
        // Parent process
        int status;
        if (waitpid(pid, &status, 0) == -1) {
            perror("Error waiting for child process");
        }
    }
}
