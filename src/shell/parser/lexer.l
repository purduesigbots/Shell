
%{
    #include <iostream>
    #include <cstdlib>
    #include "shell/parser/lexer.hpp"
    #include "shell/parser/parser.y.hpp"
%}

%option c++

%option noyywrap
%option nodefault

%option yyclass="Lexer"
%option prefix="shell_"

%%

[^ \n\t\r]+ {
    return shell::Parser::make_TOKEN(yytext);
}

[\n\t ] {
    /* Ignore whitespace */
}

. {
    std::cerr << "Lexer: Unknown Character \"" << yytext << "\"" << std::endl;
}

%%


