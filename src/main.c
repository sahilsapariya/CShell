#include<stdio.h>
#include<unistd.h>
#include "builtin.h"


int main() {


    char cwd[1024];
    getlogin_r(cwd, sizeof(cwd));

    print_prompt();

    exit_shell();

    return 0;
}