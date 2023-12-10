/**
 * @file shell.hpp
 * 
 * @brief Shell instance public API.
 */

#ifndef SHELL_HPP_INCLUDED
#define SHELL_HPP_INCLUDED

#include <stdio.h>
#include <iostream>
#include <map>
#include <string>
#include <functional>

#include "shell/parser/parser.hpp"
#include "shell/parser/lexer.hpp"
#include "shell/parser/location.hpp"
#include "shell/data.hpp"
#include "shell/command.hpp"

namespace shell {

/**
 * @brief instance of the shell. This lets the users' C++ programs interact with the shell.
 */
class Shell
{
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
     * @brief Runs the shell in a non-interactive mode. 
     * 
     * @details In non-interactive mode, the shell will not write prompt strings, and will parse the entire input
     *          before running the program. 
     * 
     * @param input The input stream to read from
     * @param input The output stream to write normal output to. This is also used for the prompt
     * @param error The output stream to write errors to
     */
    void runNonInteractive(std::istream& input = std::cin, std::ostream& output = std::cout, std::ostream& error = std::cerr);
    

    /**
     * @brief Sets the prompt to use when in interactive mode
     * 
     * @param prompt The prompt string to use
     */
    void setPrompt(std::string prompt);

    /**
     * @brief Resets the user's prompt to the default
     */
    void resetPrompt();

    /**
     * @brief Adds a command to the shell environment
     * 
     * @param name The name of the command
     * @param callback The callback to call when the command is executed
     */
    void registerCommand(std::string name, CommandCallback callback);

    /**
     * @brief Adds a new unit system to the shell environment. 
     * 
     * @param systemName    The name of the new unit system.
     * @param baseUnit      The suffix to use for the base unit in the system. 
     */
    void addUnitSystem(std::string systemName, std::string baseUnit);

    /**
     * @brief Adds a new unit suffix to a the specified unit system. 
     * 
     * @param systemName    The name of the unit system to add the suffix to
     * @param unitSuffix    The suffix to use
     * @param toBaseUnit    A functor that converts the new unit suffix to the
     *                      system's base units
     * @param toUnit        A functor that converts the system's base units to 
     *                      the new unit.
     */
    void addUnitSuffix(std::string systemName,
        std::string                     unitSuffix, 
        std::function<double(double)>   toBaseUnit,
        std::function<double(double)>   toUnit
    );

private:
    std::optional<std::string>                  _userPrompt;
    std::map<std::string, CommandCallback>      _commands;

    struct UnitInfo {
        std::string                     suffix;
        std::function<double(double)>   toBaseUnit;
        std::function<double(double)>   toUnit;
    };

    struct UnitSystemInfo {
        std::string                         systemName;
        std::string                         baseUnit;
        std::map<std::string, UnitInfo>     units;
    };

    std::map<std::string, UnitSystemInfo>    unitSystems;
    std::map<std::string, std::string>       unitToSystem;

    std::optional<Number> evaluateNumberToBase(Number number) const;
    std::optional<Number> evaluateNumberToUnit(Number number, std::string unit) const;
    
    Lexer _lexer;
    Parser _parser;

    friend class Parser;
    friend class Lexer;
    friend class CommandArgs;

    friend std::ostream& operator<<(std::ostream& stream, const Shell::UnitInfo& info);
    friend std::ostream& operator<<(std::ostream& stream, const Shell::UnitSystemInfo& info);
};

} // namespace shell


#endif//SHELL_HPP_INCLUDED
