/**
 * Shell Public API
 * 
 * This file contains the public API for the shell library.
 */

#pragma once

#include <iostream>
#include <map>
#include <string> 

#include "shell/command_args.hpp"
#include "shell/tokenizer.hpp"

namespace shell {

using CommandCallback = bool(*)(const CommandArgs args);

class Shell
{
public:
    bool runInteractive(std::istream& sourceStream = std::cin);

    bool addCommand(std::string name, CommandCallback callback);

protected:
    std::map<std::string, CommandCallback>  commands;

    void parseNamedArgument(Tokenizer& tokenizer, CommandArgs& args);
    void parseCommandArguments(Tokenizer& tokenizer, CommandArgs& args);
    void parseCommand(Tokenizer& tokenizer);
    void parseStatement(Tokenizer& tokenizer);
};

} // namespace shell