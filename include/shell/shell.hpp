/*******************************************************************************
 * @file shell.hpp
 * 
 * The public API for the shell.
 ******************************************************************************/

#pragma once

#include <istream>
#include <iostream>
#include <string>
#include <map>

#include "shell/command.hpp"

namespace shell {

class Shell
{
public:
    bool runInteractive(std::istream& sourceStrea = std::cin);

    bool addCommand(std::string name, CommandCallback callback);

private:
    std::map<std::string, CommandCallback> builtinCommands;
    std::map<std::string, CommandCallback> userCommands;
};

} // namespace shell
