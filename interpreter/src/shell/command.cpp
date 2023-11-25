#include "shell/command.hpp"

namespace shell
{

std::string CommandArgs::commandName() const 
{
    return _name;
}

bool CommandArgs::getBoolean(std::string name) const
{
    auto ittr = _namedLookup.find(name);

    return ittr != _namedLookup.end() && 
        ittr->second->type == ArgumentInfo::BOOLEAN;
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

void CommandArgs::addNamedString(std::string name, std::string value)
{
    ArgumentInfo info;
    info.type = ArgumentInfo::STRING;
    info.name = name;
    info.stringValue = value;

    _arguments.push_back(info);
    _namedLookup[name] = &_arguments.back();
}

void CommandArgs::addNamedNumber(std::string name, Number value)
{
    ArgumentInfo info;
    info.type = ArgumentInfo::NUMBER;
    info.name = name;
    info.numberValue = value;

    _arguments.push_back(info);
    _namedLookup[name] = &_arguments.back();
}

void CommandArgs::addNamedBoolean(std::string name, bool value)
{
    ArgumentInfo info;
    info.type = ArgumentInfo::BOOLEAN;
    info.name = name;
    info.boolValue = value;

    _arguments.push_back(info);
    _namedLookup[name] = &_arguments.back();
}

void CommandArgs::addUnnamedString(std::string value)
{
    ArgumentInfo info;
    info.type = ArgumentInfo::STRING;
    info.name = "";
    info.stringValue = value;

    _arguments.push_back(info);
    _indexedLookup.push_back(_arguments.size() - 1);
}

void CommandArgs::addUnnamedNumber(Number value)
{
    ArgumentInfo info;
    info.type = ArgumentInfo::NUMBER;
    info.name = "";
    info.numberValue = value;

    _arguments.push_back(info);
    _indexedLookup.push_back(_arguments.size() - 1);
}

void CommandArgs::addUnnamedBoolean(bool value)
{
    ArgumentInfo info;
    info.type = ArgumentInfo::NUMBER;
    info.name = "";
    info.boolValue = value;

    _arguments.push_back(info);
    _indexedLookup.push_back(_arguments.size() - 1);
}




} // namespace shell
