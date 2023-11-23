/** 
 * This file contains the Bison grammer for the shell language. It is used by bison to generate the parser.
 *
 * Bison exports this parser as the "shell::Parser" class, which is then used by the Shell class to read the input.
 *
 * Misc. Notes:
 * - Since we are working in a C++ parser using variants instead of unions, there is no %union block. Instead, each
 *   token and non-terminal are marked with the type of the semantic value they contain.
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
%define api.parser.class { yyBisonParser }

// We want location data for better error reporting
%locations 

%define parse.error verbose

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
    
    #include "shell/parser/location.y.hpp"

    #include "shell/data.hpp"

    // Forward declare the dependent classes for the parser here. If we include the header files, we'll get a circular
    // dependency.
    namespace shell
    {
        class Lexer;
        class Parser; 
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
    static shell::yyBisonParser::symbol_type yylex(shell::Lexer & lexer, shell::Parser & parser)
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
%lex-param { shell::Parser & parser }

// The parameters that Parser::parse() takes. These are defined in in the order they appear in the file.
%parse-param { shell::Lexer & lexer }
%parse-param { shell::Parser & parser }

//======================================================================================================================
// TOKEN AND NONTERMINAL TYPE DEFINITIONS
//
// NOTE: Since we are using a C++ parser with variants, there is no %union block. Instead, each token and non-terminal
//       are marked with a type in angle brackets.
//======================================================================================================================

%token END 0

// These tokens each contain semantic values associated with the token. These values are extracted by the Lexer.
%token <std::string>    IDENTIFIER STRING_LITERAL
%token <bool>           BOOL_LITERAL
%token <shell::Number>  NUMBER_LITERAL 

// These tokens have no semantic value associated with them. They simply mark important parts of the code.
%token STATEMENT_END

// These tokens are defined with both a name and a string. Either can be used to refer to the token, but the string
// lets us use the specific chracter sequence of the token in the grammer below.
%token 
    EQUALS          "="
    LEFT_PAREN      "("
    RIGHT_PAREN     ")"
    COMMA           ","
    ;

// TODO: Types for non-terminals:

//======================================================================================================================
// MISC DEFINITIONS
//======================================================================================================================

// Name the start non-terminal we're going to use.
%start program

//======================================================================================================================
// PARSER RULES
// These define the grammer of the language. The Bison parser will use these rules to parse the input.
// Each rule contains a list of tokens and sub-rules that are used to match the input, and a body of C++ code that
// executes when the rule is matched with the input. 
//======================================================================================================================

%%

program
    : statement_list
    ;

statement_list
    : statement_list statement
    | statement
    ;


//----------------------------------------------------------------------------------------------------------------------    
// Statements:
// 

statement
    : statement_body STATEMENT_END
    ;

statement_body
    : command_call
    ;

command_call
    : IDENTIFIER command_args { 
        std::cout << "Calling Command \"" << $1 << "\"" << std::endl;
    }
    ;

command_args
    : command_arg_list {
        std::cout << "with arguments" << std::endl;
    }
    | {
        std::cout << "with no arguments" << std::endl;
    }
    ;

command_arg_list
    : command_arg_list command_arg {

    }
    | command_arg {

    }
    ;

command_arg
    : IDENTIFIER "=" expression {
        std::cout << "With named argument \"" << $1 << "\"" << std::endl;
    }
    | expression {
        std::cout << "With unnamed argument" << std::endl;
    }
    | IDENTIFIER {
        std::cout << "With flag \"" << $1 << "\" set" << std::endl;
    }
    ;

//----------------------------------------------------------------------------------------------------------------------
// Expressions:
// Expresssions result in a value when executed. 

expression
    : tuple_expression {
    }
    | NUMBER_LITERAL {
    }
    | BOOL_LITERAL {
    }
    | STRING_LITERAL {
    }
    ;

tuple_expression
    : "(" tuple_value_list ")" {
    }
    ;

tuple_value_list
    : expression "," tuple_value_list {
    }
    | expression {
    }
    ;

%%

// Error reporting function. This is called by Bison when it encounters a syntax error.
void shell::yyBisonParser::error(const location &loc , const std::string &message)
{
    position begin = loc.begin;
    position end  = loc.end;

    std::cerr << "Error at " << begin.filename << ":" << begin.line << ":" << begin.column << std::endl;
    std::cerr << "    " << message << std::endl;
}
