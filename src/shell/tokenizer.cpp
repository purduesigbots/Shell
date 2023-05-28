#include "shell/tokenizer.hpp"

#include <string>
#include <istream>
#include <vector>
#include <queue>
#include <numeric>

namespace shell {

const char delimiters[] = {
    '(', ')',
    '[', ']',
    '{', '}',
    ',', '.',
    '`', '!', '@', '#', '$', '%', '^', '&', '*',
    '|', ':', '<', '>', '/',
    '-', '=', '+',
};

Tokenizer::Tokenizer(std::istream& istream)
: stream(istream)
{

}

Token Tokenizer::next() 
{
    // If there are no tokens in the queue, we need to read in at least 1 token
    if(heldTokens.size() < 1) {
        readNumTokens(1);
    }

    // Return the first token in the queue
    Token front = heldTokens.front();
    heldTokens.pop_front();
    return front;
}

Token& Tokenizer::peek(size_t pos) 
{
    if(heldTokens.size() < pos + 1)
        readNumTokens(1);

    return heldTokens[pos];
}

bool Tokenizer::hasNext() 
{
    return heldTokens.size() > 0 || stream.good();
}

void Tokenizer::readNumTokens(size_t min)
{
    size_t startNumTokens = heldTokens.size();
    std::string string;

    while(heldTokens.size() - startNumTokens < min) {
        readToken();
    }
}

void Tokenizer::readToken() 
{
    eatWhitespace();

    if(stream.peek() == ';' || stream.peek() == '\n') {
        stream.ignore(1);
        heldTokens.push_back(Token::endOfStatement());
    }
    else if(isDelimiter(stream.peek())) {
        char c = stream.get();
        heldTokens.push_back(Token::delimiter(c));
    }
    else if(std::isdigit(stream.peek()))
        readNumber();
    else if(std::isalpha(stream.peek()))
        readIdentifier();
    else if(stream.peek() == '\"' || stream.peek() == '\'')
        readString();
    else if(stream.peek() == '?') {
        stream.ignore(1);
        heldTokens.push_back(Token::endOfFile());
    }
    else {
        throw "Tokenizer Error: invalid token";
    }
}

void Tokenizer::readIdentifier()
{
    std::string value;

    while(
        std::isalpha(stream.peek()) ||
        std::isdigit(stream.peek()) ||
        stream.peek() == '_'
    ) {
        value += (char)stream.get();
    }

    heldTokens.push_back(Token::identifier(value));
}

void Tokenizer::readNumber()
{
    std::string numberPart;
    std::string suffixPart;

    while(std::isdigit(stream.peek()) || stream.peek() == '.') {
        numberPart += (char)stream.get();
    }

    while(std::isalpha(stream.peek()) && !isDelimiter(stream.peek())) {
        suffixPart += (char)stream.get();
    }

    float value = std::stod(numberPart);

    heldTokens.push_back(Token::number(value, suffixPart));
}

void Tokenizer::readString()
{
    char startDelim = stream.get();
    std::string str{};

    while(stream.peek() != startDelim) {
        str += stream.get();
    }
    stream.ignore(1);


    heldTokens.push_back(Token::string(str));
}

void Tokenizer::eatWhitespace() {
    while(std::isspace(stream.peek()) && stream.peek() != '\n') {
        stream.ignore(1);
    }
}

bool Tokenizer::isDelimiter(char c) {
    for(char d : delimiters) {
        if(d == c) {
            return true;
        }
    }

    return false;
}

} // namespace shell