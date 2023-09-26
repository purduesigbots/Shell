#ifndef SHELL_HPP_INCLUDED
#define SHELL_HPP_INCLUDED

#include <stdio.h>
#include <iostream>
#include <map>
#include <string>

#include "shell/parser/parser.hpp"
#include "shell/parser/lexer.hpp"
#include "shell/parser/location.y.hpp"
#include "shell/types.hpp"
#include "shell/command.hpp"

namespace shell {

/**
 * @brief instance of the shell. This lets the users' C++ programs interact with the shell.
 */
class Shell
{
    /* NOTE: The shell object acts as a driver for the Bison parser. 
     */
public:
    
    Shell();
    ~Shell();

    /**
     * @brief Runs the shell in interactive mode
     * 
     * @param input The input stream to read from
     * @param input The output stream to write normal output to. This is also used for the prompt
     * @param error The output stream to write errors to
     */
    void runInteractive(std::istream& input = std::cin, std::ostream& output = std::cout, std::ostream& error = std::cerr);

    /**
     * @brief Sets the prompt to use when in interactive mode
     * 
     * @param prompt The prompt string to use
     */
    void setPrompt(std::string prompt);

    /**
     * @brief Adds a command to the shell environment
     * 
     * @param name The name of the command
     * @param callback The callback to call when the command is executed
     */
    void registerCommand(std::string name, CommandCallback callback);

private:
    std::string                                 _prompt;
    std::map<std::string, CommandCallback>      _commands;

    Lexer _lexer;
    Parser _parser;

    friend class Parser;
    friend class Lexer;
};

} // namespace shell


#endif//SHELL_HPP_INCLUDED