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

    /// @brief      Returns a named argument as a string, if one exists.
    /// @param name The name of the argument to get
    /// @return     An optional argument containing the string, or std::nullopt
    ///             if the argument does not exist.
    std::optional<std::string> getString(std::string name) const;

protected:
    friend class Shell;
    friend class Parser;

    void addFlag(std::string name);
    void addString(std::string name, std::string value);
    void addNumber(std::string name, double value, std::string suffix = "");

    std::string                             name;
    std::vector<ArgumentInfo>               arguments; 
    std::map<std::string, ArgumentInfo*>    namedLookup;
};

} // namespace shell
