#pragma once

#if !defined(yyFlexLexerOnce)

#undef yyFlexLexer
#define yyFlexLexer shell_FlexLexer

#include <FlexLexer.h>

#endif

#undef YY_DECL

#include "shell/parser/parser.y.hpp"
#define YY_DECL shell::parser::Parser::symbol_type shell::parser::Scanner::getNextToken()


namespace shell::parser
{

class Interpreter;

class Scanner : public yyFlexLexer 
{
public:
    Scanner(Interpreter& driver) : m_driver(driver) {}

    virtual ~Scanner() {}

    virtual shell::parser::Parser::symbol_type getNextToken();

private: 
    Interpreter& m_driver;
};

}