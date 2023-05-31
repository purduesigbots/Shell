#pragma once

#include <functional>
#include <optional>
#include <string>

#include "types.hpp"

namespace shell {

/**
 * @brief     A helper class for handling the arguments passed to a command
 */
class CommandArgs
{
public:
    /// @brief      Returns the name that was used to call this callback
    /// @return     The name of the command that called this callback
    std::string getCalledName() const;

    /// @brief      Returns whether or not the command has a flag with the given name.
    /// @param name The name of the flag
    /// @return     True if the command has a flag with the given name, false otherwise.
    bool hasFlag(std::string name) const;

    /// @brief      Gets a named argument as a number.
    /// @param name The name of the argument
    /// @return     An optional containing the number value, or std::nullopt if the argument was not provided.
    std::optional<Number> getNumber(std::string name) const;

    /// @brief                  Gets a named argument as a number, returning a default value if the argument was not provided.
    /// @param name             The name of the argument
    /// @param defaultValue     The default value of the argument
    /// @param defaultSuffix    The default suffix of the argument
    /// @return                 The number value of the argument, or the default value if the argument was not provided.
    Number getNumber(std::string name, double defaultValue, std::string defaultSuffix = "") const;

    /// @brief              Gets a named argument as a number, returning a default value if the argument was not provided.
    /// @param name         The name of the argument
    /// @param defaultValue The default value of the argument
    /// @return             The number value of the argument, or the default value if the argument was not provided.
    Number getNumber(std::string name, Number defaultValue) const;

    /// @brief      Gets a named argument as a string, returning std::nullopt if the argument was not provided.
    /// @param name The name of the argument
    /// @return     An std::optional containing the string value, or std::nullopt if the argument was not provided.
    std::optional<std::string> getString(std::string name) const;

    /// @brief              Gets a named argument as a string, returning a default value if the argument was not provided.
    /// @param name         The name of the argument
    /// @param defaultValue The default value of the argument
    /// @return             The string value of the argument, or the default value if the argument was not provided.
    std::string getString(std::string name, std::string defaultValue) const;

protected:
};

/**
 * @brief      A callback function for a command
 * 
 * @param args The arguments passed to the command
 * @returns    True if there were no errors parsing the arguments, false otherwise.
 */
using CommandCallback = std::function<bool(CommandArgs)>;

} // namespace shell
