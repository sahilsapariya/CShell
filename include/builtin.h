#ifndef BUILTIN_H
#define BUILTIN_H

#define PROMPT_MSG "cshell=# "

// Function prototype to disply working directory
void print_prompt();

// Function prototype to end program
void exit_shell();

// Function prototype to read user input
void read_input(char *input);

// Function prototype to display output
void display_output(char *output);

#endif
