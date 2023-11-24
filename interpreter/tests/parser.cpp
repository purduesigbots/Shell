#include <stdio.h>

#include <iostream> 
#include <thread>
#include <chrono>

#include "shell/shell.hpp"
#include "shell/data.hpp"

bool exitCallback(shell::CommandArgs args)
{
    std::cout << "Goodbye..." << std::endl;

    exit(0);

    return false;
}

bool delayCallback(shell::CommandArgs args)
{
    if(auto delayOpt = args.getNumber("delay")) {
        shell::Number delay = delayOpt.value();

        int microseconds = 0;

        if(delay.suffix == "ms")
            microseconds = delay.value * 1000;
        else if (delay.suffix == "s")
            microseconds = delay.value * 1000000;
        else if (delay.suffix == "m")
            microseconds = delay.value * 60000000;
        else if (delay.suffix == "us") 
            microseconds = delay.value;
        else {
            std::cerr << "Invalid delay unit: \"" << delay.suffix << "\"" << std::endl;
            return false;
        }

        std::this_thread::sleep_for(std::chrono::microseconds(microseconds));

        std::cout << "Delay complete" << std::endl;

        return true; 
    }
    else {
        std::cerr << "No delay specified" << std::endl;
        return false;
    }
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

    shell.runInteractive();
}