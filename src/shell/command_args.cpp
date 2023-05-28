#include "shell/command_args.hpp"

#include <string>

namespace shell {

std::string CommandArgs::commandName() const
{
    return name;
}

bool CommandArgs::hasFlag(std::string name) const
{
    auto itr = namedLookup.find(name);

    return itr != namedLookup.end() && itr->second->type == ArgumentInfo::FLAG;
}

std::optional<Number> CommandArgs::getNumber(std::string name) const
{
    auto itr = namedLookup.find(name);

    if(itr != namedLookup.end() && itr->second->type == ArgumentInfo::NUMBER)
        return itr->second->numberValue;

    return std::nullopt;
}

std::optional<std::string> CommandArgs::getString(std::string name) const
{
    auto itr = namedLookup.find(name);

    if(itr != namedLookup.end() && itr->second->type == ArgumentInfo::STRING)
        return itr->second->stringValue;

    return std::nullopt;
}

void CommandArgs::addFlag(std::string name)
{
    ArgumentInfo info;
    info.name = name;
    info.type = ArgumentInfo::FLAG;
    info.boolValue = true;

    arguments.push_back(info);
    namedLookup[name] = &arguments.back();
}

void CommandArgs::addString(std::string name, std::string value)
{
    ArgumentInfo info;
    info.name = name;
    info.type = ArgumentInfo::STRING;
    info.stringValue = value;

    arguments.push_back(info);
    namedLookup[name] = &arguments.back();
}

void CommandArgs::addNumber(std::string name, double value, std::string suffix)
{
    ArgumentInfo info;
    info.name = name;
    info.type = ArgumentInfo::NUMBER;
    info.numberValue.value = value;
    info.numberValue.suffix = suffix;

    arguments.push_back(info);
    namedLookup[name] = &arguments.back();
}


} // namespace shell
