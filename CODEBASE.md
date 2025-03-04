# File Naming Conventions and Folder Structure:

#### **Folder Structure:**

```
custom-shell/
├── include/          # Header files (.h)
│   ├── builtins.h    # Header for built-in commands (e.g., cd, exit)
│   ├── executor.h    # Header for command execution logic
│   ├── parser.h      # Header for parsing commands
│   ├── shell.h       # Main shell definitions and utilities
├── src/              # Source files (.c)
│   ├── builtins.c    # Source for built-in commands logic
│   ├── executor.c    # Source for command execution
│   ├── parser.c      # Source for command parsing
│   ├── shell.c       # Source for general shell setup, environment variables
│   └── main.c        # Entry point for the shell program
├── tests/            # Unit tests or manual testing scripts
│   └── test_builtins.c
└── Makefile          # Makefile for building the project
```

### Feature Breakdown and Corresponding Files:

1. **Main Shell (`main.c` and `shell.h/.c`):**
   - **Purpose**: The entry point for your shell. This file handles the initialization of the shell, reading user input, and delegating tasks like parsing and executing commands to other modules.
   - **Functions**: Initialization, shell loop, environment setup.
   - **File Names**:
     - `src/main.c`: Main logic for running the shell.
     - `include/shell.h`: Declarations for shell-related utility functions.
     - `src/shell.c`: Implementations of shell utilities like reading input.

2. **Command Parsing (`parser.h/.c`):**
   - **Purpose**: To break down the user input into individual commands and arguments.
   - **Functions**: Tokenizing commands, handling arguments, detecting I/O redirection or pipes.
   - **File Names**:
     - `include/parser.h`: Function prototypes for parsing commands.
     - `src/parser.c`: Implementations for parsing logic.

3. **Command Execution (`executor.h/.c`):**
   - **Purpose**: To actually execute the parsed commands by using system calls (`fork()`, `exec()`, etc.).
   - **Functions**: Executing external programs, handling pipes, redirection, and background processes.
   - **File Names**:
     - `include/executor.h`: Prototypes for command execution.
     - `src/executor.c`: Implementations of execution logic.

4. **Built-in Commands (`builtins.h/.c`):**
   - **Purpose**: Handle built-in shell commands such as `cd`, `exit`, `echo`, `pwd`, etc.
   - **Functions**: Implementations for each built-in command.
   - **File Names**:
     - `include/builtins.h`: Prototypes for built-in commands.
     - `src/builtins.c`: Implementation of built-in commands.

---

### Example File Contents:

**`include/shell.h`** (Shell setup and utilities):
```c
#ifndef SHELL_H
#define SHELL_H

// Shell initialization function
void initialize_shell();

// Function to read user input
char *read_input();

// Function to display the shell prompt
void display_prompt();

#endif
```

**`src/shell.c`**:
```c
#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

void initialize_shell() {
    // Any environment setup or initialization here
    printf("Initializing custom shell...\n");
}

char *read_input() {
    char *line = NULL;
    size_t len = 0;
    getline(&line, &len, stdin);  // Read a line of input
    return line;
}

void display_prompt() {
    printf("custom-shell$ ");
}
```

---

**`include/parser.h`** (Command parsing):
```c
#ifndef PARSER_H
#define PARSER_H

// Function to parse input command line
char **parse_command(char *line);

#endif
```

**`src/parser.c`**:
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

#define MAX_TOKENS 64
#define TOKEN_DELIM " \t\r\n"

// Function to parse the command
char **parse_command(char *line) {
    int bufsize = MAX_TOKENS, position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    if (!tokens) {
        fprintf(stderr, "Allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, TOKEN_DELIM);
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += MAX_TOKENS;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens) {
                fprintf(stderr, "Allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, TOKEN_DELIM);
    }
    tokens[position] = NULL; // Null-terminate the array of tokens
    return tokens;
}
```

---

**`include/executor.h`** (Command execution):
```c
#ifndef EXECUTOR_H
#define EXECUTOR_H

// Function to execute a parsed command
int execute_command(char **args);

#endif
```

**`src/executor.c`**:
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "executor.h"
#include "builtins.h"

// Execute the command by forking and using execvp
int execute_command(char **args) {
    pid_t pid;
    int status;

    // Check for built-in commands
    if (is_builtin_command(args)) {
        return run_builtin_command(args);
    }

    pid = fork();  // Fork the process
    if (pid == 0) {
        // Child process: Execute the command
        if (execvp(args[0], args) == -1) {
            perror("execvp");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        // Forking failed
        perror("fork");
    } else {
        // Parent process: Wait for the child to finish
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;  // Return success
}
```

---

**`include/builtins.h`** (Built-in commands):
```c
#ifndef BUILTINS_H
#define BUILTINS_H

// Function to check if a command is built-in
int is_builtin_command(char **args);

// Function to execute built-in commands
int run_builtin_command(char **args);

// Built-in command functions
int shell_cd(char **args);
int shell_exit(char **args);

#endif
```

**`src/builtins.c`**:
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "builtins.h"

// Check if a command is built-in
int is_builtin_command(char **args) {
    if (strcmp(args[0], "cd") == 0) {
        return 1;
    } else if (strcmp(args[0], "exit") == 0) {
        return 1;
    }
    return 0;
}

// Run the built-in command
int run_builtin_command(char **args) {
    if (strcmp(args[0], "cd") == 0) {
        return shell_cd(args);
    } else if (strcmp(args[0], "exit") == 0) {
        return shell_exit(args);
    }
    return 0;
}

// Change directory (cd) command
int shell_cd(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "cd: expected argument\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror("cd");
        }
    }
    return 1;
}

// Exit the shell
int shell_exit(char **args) {
    exit(0);
}
```

---

### How to Use:

1. **To compile the project:**
   You can write a `Makefile` to compile the project. Example `Makefile`:

```make
   CC = gcc
   CFLAGS = -I./include

   all: myshell

   myshell: src/main.o src/shell.o src/parser.o src/executor.o src/builtins.o
       $(CC) -o myshell src/main.o src/shell.o src/parser.o src/executor.o src/builtins.o

   src/main.o: src/main.c
       $(CC) $(CFLAGS) -c src/main.c -o src/main.o

   src/shell.o: src/shell.c
       $(CC) $(CFLAGS) -c src/shell.c -o src/shell.o

   src/parser.o: src/parser.c
       $(CC) $(CFLAGS) -c src/parser.c -o src/parser.o

   src/executor.o: src/executor.c
       $(CC) $(CFLAGS) -c src/executor.c -o src/executor.o

   src/builtins.o: src/builtins.c
       $(CC) $(CFLAGS) -c src/builtins.c -o src/builtins.o

   clean:
       rm -f myshell src/*.o
```
