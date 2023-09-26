#include "shell/command.hpp"

namespace shell
{

std::string CommandArgs::commandName() const 
{
    return _name;
}

bool CommandArgs::hasFlag(std::string name) const
{
    auto ittr = _namedLookup.find(name);

    return ittr != _namedLookup.end() && 
        ittr->second->type == ArgumentInfo::FLAG;
}


std::optional<Number> CommandArgs::getNumber(std::string name) const
{
    auto ittr = _namedLookup.find(name);

    if(ittr != _namedLookup.end() && 
       ittr->second->type == ArgumentInfo::NUMBER) {
        return ittr->second->numberValue;
    }

    return std::nullopt;
}

std::optional<Number> CommandArgs::getNumber(size_t index) const
{
    if(index < 0 || index >= _indexedLookup.size())
        return std::nullopt;

    size_t argIndex = _indexedLookup[index];
    if(argIndex < 0 || argIndex >= _arguments.size())
        return std::nullopt;

    if(_arguments[argIndex].type == ArgumentInfo::NUMBER)
        return _arguments[argIndex].numberValue;

    return std::nullopt;
}

std::optional<std::string> CommandArgs::getString(std::string name) const
{
    auto ittr = _namedLookup.find(name);

    if(ittr != _namedLookup.end() && 
       ittr->second->type == ArgumentInfo::STRING) {
        return ittr->second->stringValue;
    }

    return std::nullopt;
}

std::optional<std::string> CommandArgs::getString(size_t index) const
{
    if(index < 0 || index >= _indexedLookup.size())
        return std::nullopt;

    size_t argIndex = _indexedLookup[index];
    if(argIndex < 0 || argIndex >= _arguments.size())
        return std::nullopt;

    if(_arguments[argIndex].type == ArgumentInfo::NUMBER)
        return _arguments[argIndex].stringValue;

    return std::nullopt;
}

size_t CommandArgs::numberOfNamedArguments() const
{
    return _namedLookup.size();
}

size_t CommandArgs::numberOfUnnamedArguments() const
{
    return _indexedLookup.size();
}

size_t CommandArgs::totalNumberOfArguments() const
{
    return _arguments.size();
}


} // namespace shell
