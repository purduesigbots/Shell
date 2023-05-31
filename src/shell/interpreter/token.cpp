#include "shell/interpreter/token.hpp"

#include <string>

#include "shell/types.hpp"

namespace shell::interpreter
{

//==============================================================================
// Token comparison methods: Used by the parser to determine what type of token
// it is looking at and whether it is the token it is expecting.
//==============================================================================

bool Token::isDelimiter() const
{
    return type == DELIMITER;
}

bool Token::isDelimiter(char value) const
{
    return type == DELIMITER && charValue == value;
}

bool Token::isIdentifier() const
{
    return type == IDENTIFIER;
}

bool Token::isIdentifier(std::string value) const
{
    return type == IDENTIFIER && stringValue == value;
}

bool Token::isNumber() const
{
    return type == NUMBER_LITERAL;
}

bool Token::isNumber(double value, std::string suffix) const
{
    return type == NUMBER_LITERAL && numberValue == value && stringValue == suffix;
}

bool Token::isNumber(Number value) const
{
    return type == NUMBER_LITERAL && numberValue == value.value && stringValue == value.suffix;
}

//==============================================================================
// Static methods for creating tokens: Similar rust constructors. 
// These are static methods because they are more clear and concise than normal
// constructors
//==============================================================================

Token Token::keyword(std::string value)
{
    Token token;
    token.type = KEYWORD;
    token.stringValue = value;
    return token;
}

Token Token::identifier(std::string value)
{
    Token token;
    token.type = IDENTIFIER;
    token.stringValue = value;
    return token;
}

Token Token::delimiter(char value)
{
    Token token;
    token.type = DELIMITER;
    token.charValue = value;
    return token;
}

Token Token::stringLiteral(std::string value)
{
    Token token;
    token.type = STRING_LITERAL;
    token.stringValue = value;
    return token;
}


} // namespace shell::internal