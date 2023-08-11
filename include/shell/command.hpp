#pragma once

#include <optional>
#include <string>
#include <vector>
#include <map>

#include "shell/types.hpp"
namespace shell
{

struct ArgumentInfo
{
    enum 
    {
        FLAG,
        NUMBER,
        STRING,
    };

    std::string name;
    int         type;

    std::string stringValue;
    Number      numberValue;
    bool        boolValue;
};

class CommandArgs
{
public:
    /// @brief      Returns the name of the command the calls the callback
    /// @return     The command's name
    std::string commandName() const;

    /// @brief      Returns whether there's a flag argument with the given name
    /// @param name The name of the flag to check for
    /// @return     True if the flag is passed to the command, false otherwise
    bool hasFlag(std::string name) const;

    /// @brief      Returns a named argument as a number, if one exists.
    /// @param name The name of the argument to get
    /// @return     An optional object containing the number, or std::nullopt if
    ///             the argument does not exist.
    std::optional<Number> getNumber(std::string name) const;

    /// @brief          Returns the nth argument as a number, if it is a number.
    /// @param index    The index to the unnamed argument list
    /// @return         An optional object containing the number, or std::nullopt if the nth argument doesn't exist
    ///                 or is not a number.
    std::optional<Number> getNumber(size_t index) const;

    /// @brief      Returns a named argument as a string, if one exists.
    /// @param name The name of the argument to get
    /// @return     An optional argument containing the string, or std::nullopt
    ///             if the argument does not exist.
    std::optional<std::string> getString(std::string name) const;
    
    /// @brief          Returns the nth argument as a string, if it is a string.
    /// @param index    The index to the unnamed argument list
    /// @return         An optional object containing the number, or std::nullopt if the nth argument doesn't exist
    ///                 or is not a number.
    std::optional<std::string> getString(size_t index) const;

    size_t numberOfNamedArguments() const;
    size_t numberOfUnnamedArguments() const;
    size_t totalNumberOfArguments() const;

protected:
    friend class Shell;
    friend class Parser;

    void addFlag(std::string name);
    void addString(std::string name, std::string value);
    void addNumber(std::string name, double value, std::string suffix = "");

    // The name that was used to call the command. This is here in case the same callback is used for multiple aliases
    // of a given command
    std::string                             _name;

    // A list of all the arguments passed to the command, regardless of named or not.
    std::vector<ArgumentInfo>               _arguments; 

    // A map associating named arguments with their value
    std::map<std::string, ArgumentInfo*>    _namedLookup;

    // A list of the indices of the unnamed arguments
    std::vector<size_t>                     _indexedLookup;
};

using CommandCallback = bool(*)(const CommandArgs args);

} // namespace shell
