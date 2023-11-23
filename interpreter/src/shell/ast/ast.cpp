#include "shell/ast/ast.hpp"

#include <optional>

#include "shell/data.hpp"

namespace shell {

bool AstNode::isLiteral() const
{
    return _type >= NUMBER_LITERAL &&
        _type <= STRING_LITERAL
        ;
}

bool AstNode::isExpression() const
{
    return isLiteral()
        ;
}

bool AstNode::isStatement() const
{
    return _type == COMMAND_CALL
        ;
}

std::optional<TypeInfo> AstNode::getType() const
{
    switch(_type)
    {
    case NUMBER_LITERAL:
        return TypeInfo::makeNumber();
    case BOOLEAN_LITERAL:
        return TypeInfo::makeBoolean();
    case STRING_LITERAL:
        return TypeInfo::makeString();

    // This AST node does not have a type
    default:
        return std::nullopt;
    }
}

std::optional<Value> AstNode::evaluate() const
{
    // Only expressions can be evaluated
    if(!isExpression())
        return std::nullopt;
    
    // TODO: evaluate and return a value based on the AstType
    // Literals will be a simple case, but when opertors are added,
    // things will get more complex. 
    return std::nullopt;
}

void AstNode::print(std::ostream& stream, int indent) const
{
    const char* INDENT_STR = "  ";

    for(int i = 0; i < indent; i++)
        stream << INDENT_STR;

    // Print the name and semantic data for this AstNode
    switch(_type)
    {
    case NONE:
        stream << "NONE" << std::endl;
        break;
    case INVALID:
        stream << "INVALID" << std::endl;
        break;
    case NUMBER_LITERAL:
        stream << "NUMBER_LITERAL: <value>" << std::endl;
        break;
    case BOOLEAN_LITERAL:
        stream << "BOOLEAN_LITERAL: <value>" << std::endl;
        break;
    case STRING_LITERAL:
        stream << "STRING_LITERAL: <value>" << std::endl;
        break;
    default:
        stream << "UNKOWN_NODE_TYPE" << std::endl;
        break;
    };

    // Print all the children in this AST tree
    for(const AstNode& child : _children)
        child.print(stream, indent + 1);
}

} // namespace shell
