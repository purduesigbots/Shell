#pragma once

#include <optional>
#include <vector>

#include "shell/data.hpp"

#include "shell/parser/location.hpp"

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

        TUPLE_EXPRESSION,
    };

    AstNode() 
    : _type(NONE)
    {}
    
    ~AstNode() {}

    bool isLiteral() const;

    bool isExpression() const;

    bool isStatement() const;
    
    std::optional<TypeInfo> getType() const;

    std::optional<Value> evaluate() const; 

    void print(std::ostream& stream, int indent = 0) const;

    // Static factory methods
    static AstNode makeNone(Location location);

    static AstNode makeNumberLiteral(Number value, Location location);
    static AstNode makeBooleanLiteral(bool value, Location location);
    static AstNode makeStringLiteral(std::string value, Location location);

    static AstNode makeNamedCommandArg(std::string name, AstNode value, Location location);
    static AstNode makeUnnamedCommandArg(AstNode value, Location location);

    static AstNode makeCommand(std::string name, std::vector<AstNode> args, Location location);

    static AstNode makeTupleExpression(std::vector<AstNode> elements, Location location);

private:
    AstNode(int type, Location location)
    : _type{type}, _location{location}
    {}


    union {
        Number*             _numberValue;
        std::string*        _stringValue;
        bool                _booleanValue;
    };

    int                     _type;
    Location                _location;
    std::vector<AstNode>    _children;
};

} // namespace shell
