
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

%code requires
{
    #include <iostream>
    #include <string>
    
    namespace shell
    {
        class Lexer;
        class Shell;
    }
}

%code top
{
    #include <iostream>

    #include "shell/shell.hpp"

    static shell::Parser::symbol_type yylex(shell::Lexer & lexer, shell::Shell & driver)
    {
        return lexer.get_next_token();
    }

    using namespace shell;
}

%lex-param { shell::Lexer & lexer }
%lex-param { shell::Shell & driver }

%parse-param { shell::Lexer & lexer }
%parse-param { shell::Shell & driver }


%token <std::string> TOKEN;

%start program

%%

program
    : TOKEN { std::cout << $1 << '\n'; }
    ;


%%

void shell::Parser::error(std::string const& message)
{
    std::cerr << "Error: " << message << '\n';
}
