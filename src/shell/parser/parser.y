
%require "3.2"

// We want to generate a C++ parser rather than a C parser.
%language "C++"

// Tell Bison to use a C++ variant for the value type. This allows us to use any
// C++ type as the value type. Without this, we would be limited to using only
// plain old data types.
%define api.value.type variant

// Tell Bison to use token constructors. This forces type safty with our tokens,
// so that 
%define api.token.constructor

%define api.parser.class { Parser }

%define api.namespace { shell::parser }

%code requires
{
    #include "shell/parser/scanner.hpp"
    #include "shell/parser/parser.y.hpp"
    
    namespace shell::parser
    {
        class Scanner;
        class Parser;
    }
}

%code top
{
    #include "shell/parser/scanner.hpp"
    #include "shell/parser/parser.y.hpp"

    static shell::parser::Parser::symbol_type yylex(shell::parser::Scanner& scanner, shell::parser::Interpreter& interpreter)
    {
        return scanner.yylex();
    }
}

%{

#include <stdio.h>

void yyerror(const char* s) {
    printf("Error: %s\n", s);
}    

extern int yylex();

%}

%token IDENTIFIER
%token NUMBER_LITERAL
%token STRING_LITERAL
%token VARIABLE_REF
%token STATEMENT_END

%start program

%%

program
    : statement_list {
        printf("program\n");
    }
    | /* empty */
    ;

statement_list
    : statement statement_list {
        printf("statement list\n");
    }
    | statement {
        printf("statement list end\n");
    }
    ;

statement
    : command_call STATEMENT_END {
        printf("statement\n");
    }
    ;

command_call
    : IDENTIFIER command_arg_list {
        printf("command call with list\n");
    }
    | IDENTIFIER {
        printf("command call\n");
    }
    ;

command_arg_list
    : command_arg_list command_arg {
        printf("command arg list\n");
    }
    | command_arg {
        printf("command arg list end\n");
    }
    ;

command_arg
    : IDENTIFIER '=' expression {
        printf("named command arg\n");
    }
    | IDENTIFIER {
        printf("named flag\n");
    }
    | expression {
        printf("nameless arg\n");
    }
    ;

expression
    : NUMBER_LITERAL
    | STRING_LITERAL
    ;

%%

