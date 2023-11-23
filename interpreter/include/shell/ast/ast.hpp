#pragma once

#include <optional>
#include <vector>

#include "shell/data.hpp"

namespace shell {

class AstNode
{
public:
    enum 
    {
        NONE,                   // No children
        INVALID,                

        NUMBER_LITERAL,         // No children
        BOOLEAN_LITERAL,        // No children
        STRING_LITERAL,         // No children

        COMMAND_CALL,           // 
        COMMAND_NAMED_ARG,
        COMMAND_UNNAMED_ARG,
    };

    bool isLiteral() const;

    bool isExpression() const;

    bool isStatement() const;
    
    std::optional<TypeInfo> getType() const;

    std::optional<Value> evaluate() const; 

    void print(std::ostream& stream, int indent = 0) const;

private:
    int                     _type;
    std::vector<AstNode>    _children;
};

} // namespace shell
