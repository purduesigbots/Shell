#pragma once

#include <string>
#include <memory>
#include <variant>

namespace legs {

class Token
{
public:
    ~Token();

    enum {
        TYPE_IDENTIFIER,
        TYPE_NUMBER,
        TYPE_STRING,
        TYPE_DELIMITER,
        TYPE_END_OF_STATEMENT,
        TYPE_END_OF_FILE
    };

    const int getType() const { return type; }
  
    static Token identifier(std::string value);
    static Token number(float value, std::string suffix);
    static Token string(std::string value);
    static Token delimiter(char value);
    static Token endOfStatement();
    static Token endOfFile();

    std::string     strValue = "";
    float           fltValue = 0.0;
    char            chrValue = '\0';

private:
    Token(int _type);
    Token(int _type, std::string _strValue);
    Token(int _type, float _floatValue);
    Token(int _type, char _charValue);

    int type;
};

/* Define an operator overload to print tokens with std::cout */
std::ostream& operator<<(std::ostream& stream, const Token& token);

} // namespace legs