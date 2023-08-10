#ifndef LEXER_HPP_INCLUDED
#define LEXER_HPP_INCLUDED

#if !defined(yyFlexLexerOnce)
    #undef yyFlexLexer
    #define yyFlexLexer shell_FlexLexer
    #include <FlexLexer.h>
#endif

#undef YY_DECL
#define YY_DECL shell::Parser::symbol_type shell::Lexer::get_next_token()

#include "shell/parser/parser.hpp"

namespace shell {

    class Shell;

    class Lexer : public yyFlexLexer
    {
    public:
        Lexer(Shell& driver) : _driver(driver) {}

        virtual ~Lexer() {}

        virtual shell::Parser::symbol_type get_next_token();

    private:
        shell::location _currentLocation;

        void updateLocation() { printf("UPDATING LOCATION"); }

        Shell& _driver;
    };

} // namespace shell


#include "shell/shell.hpp"

#endif//LEXER_HPP_INCLUDED