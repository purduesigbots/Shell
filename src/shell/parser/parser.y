
%require "3.2"


%language "c++"

// Tell Bison that we want to use a variant type for semantic values rather than a union. 
// This lets us use C++ objects in the semantic values without having to worry about making
// them plain old data (POD) types.
%define api.value.type variant

// Tell Bison to use type safe interfaces instead of yylex
%define api.token.constructor

%define api.namespace { shell }
%define api.parser.class { Parser }

%code top
{
    #include <iostream>
    #include <string>
    #include "shell/parser/parser.y.hpp"
    #include "shell/parser/lexer.hpp"
    #include "shell/shell.hpp"

    static shell::Parser::symbol_type yylex(shell::Lexer& lexer, shell::Shell& driver)
    {
        return lexer.get_next_token(driver);
    }

    using namespace shell;
}

%lex-param { shell::Lexer& lexer }
%lex-param { shell::Shell& driver }

%parse-param { shell::Lexer& lexer }
%parse-param { shell::Shell& driver }


%code requires
{
    namespace shell
    {
        class Parser;
        class Lexer;
    }
}

%code
{

}

%token <std::string> token;

%start program

%%

program
    : token { std::cout << $1 << '\n'; }
    ;


%%
