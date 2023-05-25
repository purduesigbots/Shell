#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <deque>
#include <exception>

#include "legs/shell/token.hpp"

namespace legs {

/*
 * The tokenizer takes the input text stream and breaks it up into smaller
 * tokens. 
 */
class Tokenizer 
{
public:
    Tokenizer(std::istream& istream);

    Token next();
    Token& peek(size_t pos = 0); 

    bool hasNext();

protected:
    // Reads in a minimum number of tokens
    void readNumTokens(size_t min);

    void readToken();

    void readIdentifier();
    void readNumber();
    void readString();
    void eatWhitespace();
    
    bool isDelimiter(char c);

    std::istream&       stream;
    std::deque<Token>   heldTokens; /* List of tokens that aren't accepted yet*/
};

} // namespace legs

