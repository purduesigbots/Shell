#include "shell/token.hpp"

#include <string>
#include <iostream>

namespace shell {

Token::Token(int _type)
: type(_type) 
{}

Token::Token(int _type, std::string _strValue) 
: type(_type), strValue(_strValue)
{}

Token::Token(int _type, float _floatValue) 
: type(_type), fltValue(_floatValue)
{}

Token::Token(int _type, float _floatValue, std::string _suffixValue) 
: type(_type), fltValue(_floatValue), strValue(_suffixValue)
{}

Token::Token(int _type, char _charValue) 
: type(_type), chrValue(_charValue)
{}

Token::~Token()
{}

Token Token::identifier(std::string value) {
    return Token(Token::TYPE_IDENTIFIER, value);
}

Token Token::number(float value, std::string suffix) {
    return Token(Token::TYPE_NUMBER, value, suffix);
}

Token Token::string(std::string value) {
    return Token(Token::TYPE_STRING, value);
}

Token Token::delimiter(char value) {
    return Token(Token::TYPE_DELIMITER, value);
}

Token Token::endOfStatement() {
    return Token(Token::TYPE_END_OF_STATEMENT);
}

Token Token::endOfFile() {
    return Token(Token::TYPE_END_OF_FILE);
}

std::ostream& operator<<(std::ostream& stream, const Token& token) 
{
    switch(token.getType()) {
    case Token::TYPE_IDENTIFIER:
        return stream << "IDENTIFIER(\"" << token.strValue << "\")";
    case Token::TYPE_NUMBER:
        return stream << "NUMBER(" << token.fltValue << ",\"" 
            << token.strValue << "\")";
    case Token::TYPE_STRING:
        return stream << "STRING(\"" << token.strValue << "\"";
    case Token::TYPE_DELIMITER:
        return stream << "DELIMITER(\'" << token.chrValue << "\'";
    case Token::TYPE_END_OF_STATEMENT:
        return stream << "END_OF_STATEMENT";
    case Token::TYPE_END_OF_FILE:
        return stream << "END_OF_FILE";
    default:
        return stream << "INVALID TOKEN";
    }
}

} // namespace shell