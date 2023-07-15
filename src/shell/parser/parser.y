/** 
 *
 */

//======================================================================================================================
// SETTINGS FOR BISON
//======================================================================================================================

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

//======================================================================================================================
// CODE INSERTION BLOCKS
//======================================================================================================================

/* The C++ code within this block is inserted verbatum in the following locations:
 * - The top of the generated header file
 * - The top of the generated implementation file
 *
 * This is a good place to put forward declarations for any classes that are used in the grammar.
 */
%code requires
{
    // Include the libraries our parser's header needs
    #include <iostream>
    #include <string>

    // Forward declare the classes we need here.
    namespace shell
    {
        class Lexer;
        class Shell;
    }
}

/* The C++ code within this block is inserted vertatum in the following locations:
 * - The top of the generated implementation file
 *
 * None of these defintions will end up in the genereated header file. Anything that needs to be in the header should
 * be put in the %code requires block above.
 */
%code top
{
    #include <iostream>

    #include "shell/shell.hpp"

    // Since our lexer is exporting as C++ rather than C, yylex won't be defined. The parser calls yylex to get the
    // next token, so we need to define and implmenet it manually. This function simply calls the lexer's get_next_token
    // funciton.
    static shell::Parser::symbol_type yylex(shell::Lexer & lexer, shell::Shell & driver)
    {
        return lexer.get_next_token();
    }

    using namespace shell;
}

//======================================================================================================================
// PARAMETER DEFINITIONS
//======================================================================================================================

// Parameters that get passed to yylex(). For the call to yylex, they are passed in the order they appear in the file
%lex-param { shell::Lexer & lexer }
%lex-param { shell::Shell & driver }

// The parameters that Parser::parse() takes. These are defined in in the order they appear in the file.
%parse-param { shell::Lexer & lexer }
%parse-param { shell::Shell & driver }

//======================================================================================================================
// TOKEN DEFINITIONS
//======================================================================================================================
%token <std::string> TOKEN;


//======================================================================================================================
// MISC DEFINITIONS
//======================================================================================================================

// Name the start non-terminal we're going to use.
%start program


//======================================================================================================================
// PARSER RULES
//======================================================================================================================

%%

program
    : program TOKEN
    | TOKEN { std::cout << $1 << '\n'; }
    ;


%%

// Error reporting function. This is called by Bison when it encounters a syntax error.
void shell::Parser::error(std::string const& message)
{
    std::cerr << "Error: " << message << '\n';
}
