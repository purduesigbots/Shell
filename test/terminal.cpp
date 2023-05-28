#include <iostream>

#include "shell/shell.hpp"

using namespace shell;

bool testCallback(const CommandArgs args) 
{
    std::cout << "Command was called as \"" 
        << args.commandName() << "\"" << std::endl;

    if(args.hasFlag("flag"))
        std::cout << "    Flag is set" << std::endl;

    if(auto argOpt = args.getNumber("num")) {
        Number val = argOpt.value();

        std::cout << "    num = " << val.value << val.suffix << std::endl;
    }

    if(auto argOpt = args.getString("str")) {
        std::cout << "    str = " << argOpt.value() << std::endl;
    }

    return true;
}

bool exitCallback(const CommandArgs args)
{
    std::cout << "Exiting..." << std::endl;
    
    exit(0);
}

int main(int argc, char** argv)
{
    shell::Shell shell;

    shell.addCommand("test", testCallback);
    shell.addCommand("exit", exitCallback);

    shell.runInteractive();
}
