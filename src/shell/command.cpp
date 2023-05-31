#include "shell/command.hpp"

#include <functional>
#include <optional>
#include <string> 

namespace shell {

std::string CommandArgs::getCalledName() const
{
    return "";
}

bool CommandArgs::hasFlag(std::string name) const
{
    return false;
}

std::optional<Number> CommandArgs::getNumber(std::string name) const
{
    return std::nullopt;
}

Number CommandArgs::getNumber(std::string name, double defaultValue, std::string defaultSuffix) const
{
    return Number{defaultValue, defaultSuffix};
}

Number CommandArgs::getNumber(std::string name, Number defaultValue) const
{
    return defaultValue;
}

std::optional<std::string> CommandArgs::getString(std::string name) const
{
    return std::nullopt;
}

std::string CommandArgs::getString(std::string name, std::string defaultValue) const
{
    return defaultValue;
}

} // namespace shell
