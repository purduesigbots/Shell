#include "shell/ast/ast.hpp"

#include <optional>

#include "shell/data.hpp"
#include "shell/parser/location.hpp"

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
    const char* INDENT_STR = "|   ";

    for(int i = 0; i < indent; i++)
        stream << INDENT_STR;

    // Print the name and semantic data for this AstNode
    switch(_type)
    {
    case NONE:
        stream << "NONE " << _location << std::endl;
        break;
    case INVALID:
        stream << "INVALID" << std::endl;
        break;
    case NUMBER_LITERAL: {
        if(_numberValue == nullptr)
            stream << "NUMBER_LITERAL "  << _location << ": <NULL>" << std::endl;
        else
            stream  << "NUMBER_LITERAL " << _location << ": " << *_numberValue << std::endl;
        break;
    }
    case BOOLEAN_LITERAL: {
        const char* value = _booleanValue ? "true" : "false";
        stream << "BOOLEAN_LITERAL " << _location << ": " << value << std::endl;
        break;
    }
    case STRING_LITERAL: {
        const char* value = _stringValue == nullptr ? "<NULL>" : _stringValue->c_str();
        stream << "STRING_LITERAL: \"" << value << "\"" << std::endl;
        break;
    }
    case COMMAND_CALL: {
        const char* name = _stringValue == nullptr ? "<NULL>" : _stringValue->c_str();
        stream << "COMMAND_CALL "  << _location << ": \"" << name << "\"" << std::endl;
        break;
    }
    case COMMAND_NAMED_ARG: {
        const char* name = _stringValue == nullptr ? "<NULL>" : _stringValue->c_str();
        stream << "COMMAND_NAMED_ARG "  << _location << ": \"" << name << "\"" <<  std::endl;
        break;
    }
    case COMMAND_UNNAMED_ARG:
        stream << "COMMAND_UNNAMED_ARG" << _location << std::endl;
        break;
    default:
        stream << "UNKOWN_NODE_TYPE "  << _location << std::endl;
        break;
    case TUPLE_EXPRESSION:
        stream << "TUPLE_EXPRESSION " << _location << std::endl;
        break;
    };

    // Print all the children in this AST tree
    for(const AstNode& child : _children)
        child.print(stream, indent + 1);
}

bool AstNode::semanticCheck(std::ostream& errStream) const
{
    bool valid = false;

    switch(_type) 
    {
    case COMMAND_CALL: {
        for(const AstNode& child : _children) {
            if(child._type != COMMAND_NAMED_ARG || child._type != COMMAND_UNNAMED_ARG) {
                
            }
        }

    }

    }

    return valid;
}

AstNode AstNode::makeNone(Location location)
{
    AstNode newNode(NONE, location);
    return newNode;
}

AstNode AstNode::makeNumberLiteral(Number value, Location location)
{
    AstNode newNode(NUMBER_LITERAL, location);
    newNode._numberValue = new Number{value};

    return newNode;
}

AstNode AstNode::makeBooleanLiteral(bool value, Location location)
{
    AstNode newNode(BOOLEAN_LITERAL, location);
    newNode._booleanValue = value;

    return newNode;
}

AstNode AstNode::makeStringLiteral(std::string value, Location location)
{
    AstNode newNode(STRING_LITERAL, location);
    newNode._stringValue = new std::string(value);

    return newNode;
}

AstNode AstNode::makeNamedCommandArg(std::string name, AstNode value, Location location)
{
    AstNode newNode(COMMAND_NAMED_ARG, location);
    newNode._stringValue = new std::string(name);
    newNode._children.push_back(value);

    return newNode;
}

AstNode AstNode::makeUnnamedCommandArg(AstNode value, Location location)
{
    AstNode newNode(COMMAND_UNNAMED_ARG, location);
    newNode._children.push_back(value);

    return newNode;
}

AstNode AstNode::makeCommand(std::string name, std::vector<AstNode> args, Location location)
{
    AstNode newNode(COMMAND_CALL, location);
    newNode._stringValue = new std::string(name);
    newNode._children = args;

    return newNode;
}

AstNode AstNode::makeTupleExpression(std::vector<AstNode> elements, Location location)
{
    AstNode newNode(TUPLE_EXPRESSION, location);
    newNode._children = elements;

    return newNode;
}

} // namespace shell
