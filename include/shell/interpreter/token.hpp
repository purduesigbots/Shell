/*******************************************************************************
 * Abstraction for a token in the parsing stream
 ******************************************************************************/

#pragma once

#include <string> 

#include "shell/types.hpp"

namespace shell::interpreter
{

class Token
{
public:
    enum 
    {
        KEYWORD,
        IDENTIFIER,
        DELIMITER,
        NUMBER_LITERAL,
        STRING_LITERAL,

        END_OF_FILE,
    };

    bool isDelimiter() const;
    bool isDelimiter(char value) const;

    bool isIdentifier() const;
    bool isIdentifier(std::string value) const;

    bool isNumber() const;
    bool isNumber(double value, std::string suffix = "") const;
    bool isNumber(Number value) const;

    bool isEndOfFile() const; 

    
    static Token keyword(std::string value);
    static Token idnetifier(std::string value);
    static Token delimiter(char value);
    static Token stringLiteral(std::string value);
    static Token numberLiteral(double value, std::string suffix = "");
    static Token endOfFile();

private:
    Token() : type(-1), charValue(0) {}

    int type;
    union {
        std::string     stringValue;
        double          numberValue;
        char            charValue;
    };
};

} // namespace shell::internal
