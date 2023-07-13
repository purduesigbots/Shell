#pragma once

#if !defined(yyFlexLexerOnce)
    #undef yyFlexLexer
    #define yyFlexLexer shell_FlexLexer
    #include <FlexLexer.h>
#endif

#undef YY_DECL
#define YY_DECL shell::Parser::symbol_type shell::Lexer::get_next_token()

#include "shell/parser/parser.y.hpp"
#include "shell/shell.hpp"

namespace shell {

class Lexer : public yyFlexLexer
{
public:
    Lexer(Shell& driver) : _driver(driver) {}

    virtual ~Lexer() {}

    virtual shell::Parser::symbol_type get_next_token();

private:
    Shell& _driver;

};

}
