#include <stdio.h>

#include <iostream> 


#include "shell/shell.hpp"
#include "shell/types.hpp"

bool exitCallback(shell::CommandArgs args)
{
    std::cout << "Goodbye..." << std::endl;

    exit(0);

    return false;
}

bool gotoCallback(shell::CommandArgs args)
{
    std::cout << "Goto command called" << std::endl;

    return true;
}

int main(int argc, char** argv)
{
    printf("running yyparse\n");

    shell::Shell shell;

    shell.registerCommand("exit", exitCallback);
    shell.registerCommand("goto", gotoCallback);

    shell.runInteractive();
}