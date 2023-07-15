#include <stdio.h>

#include "shell/shell.hpp"

int main(int argc, char** argv)
{
    printf("running yyparse\n");

    shell::Shell shell;

    shell.runInteractive();
}