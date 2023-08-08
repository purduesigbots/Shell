#pragma once

#include <vector>
#include <map>

#include "shell/ast/expression.hpp"

namespace shell {

class Statement
{

};


class CommandCall : public Statement
{
public:

    virtual void execute();

private:

    friend class Parser;

    std::vector<Expression>             _unnamedArguments;
    std::map<std::string, Expression>   _namedArguments;
};


} // namespace shell
