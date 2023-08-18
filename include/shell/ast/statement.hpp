#pragma once

#include <vector>
#include <map>

#include "shell/ast/ast_node.hpp"
#include "shell/ast/expression.hpp"

namespace shell {

/// @brief Base class for all statements in the shell.
/// @details This class is the base class for all statements in the shell. A statement is a single
///          piece of code that can be executed. Statements end with a semicolon or newline. 
class Statement
{
public:


};

/// @brief Represents a single command call.
/// @details This class represents a single command call. Each command call has a name that the user types
///          in, and a list of arguments. Arguments can be either named or unnamed.
class CommandCall : public Statement
{
public:

    virtual void execute();

    void addNamedArgument(std::string name, Expression value) {
    }

    void addUnnamedArgument(Expression value) {
    }

private:
    // The name of the command to execute.
    std::string                         _commandName;

    // Keep all of the arguments in a single vector to make it easier to iterate over them, and to preserve
    // the order the user typed them into.
    std::vector<Expression>             _allArguments;

    // A vector that contains all of the unnamed arguments. This is a subset of _allArguments.
    std::vector<Expression*>            _unnamedArguments;

    // A map of all the named arguments. This is a subset of _allArguments.
    std::map<std::string, Expression*>   _namedArguments;
};

class CommandArg : public Statement
{

private:
    std::string     _name;
};


} // namespace shell
