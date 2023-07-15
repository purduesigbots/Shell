
%{
    #include <iostream>
    #include <cstdlib>
    #include "shell/parser/lexer.hpp"
    #include "shell/parser/parser.hpp"
%}

%option c++

%option noyywrap
%option nodefault

%option yyclass="Lexer"
%option prefix="shell_"

    //==========================================================================
    // REGULAR DEFINITIONS
    //==========================================================================

DIGIT       [0-9]
ID_START    [a-zA-Z_]
ID_CHAR     [a-zA-Z0-9_]
LETTER      [a-zA-Z]

%%

[^ \n\t\r]+ {
    std::cout << "Found TOKEN!" << std::endl;
    return shell::Parser::make_TOKEN(yytext);
}

    /* Number Literal Token */
{DIGIT}+(\.{DIGIT}*)?{LETTER}* {
    std::cout << "Token: NUMBER_LITERAL \"" << yytext << "\"" << std::endl;
}

    /* Ignore the rest of the whitespace */
[\n\t ] {
    /* Ignore whitespace */
}

. {
    std::cerr << "Lexer: Unknown Character \"" << yytext << "\"" << std::endl;
}

%%


