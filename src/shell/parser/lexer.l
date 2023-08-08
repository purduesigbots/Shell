    /*
     * lexer.l
     *
     * This file contains the lexer (aka tokenizer) for this language. The functionality here gets exported to the
     * Lexer class after Flex compiles this program.
     */

%{
    #include <iostream>
    #include <cstdlib>
    #include "shell/parser/lexer.hpp"
    #include "shell/parser/parser.hpp"

    #include "shell/types.hpp"
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

    /* Comment "Token" */
\#[^\n]*\n {
    /* Purposefully ignore the comment */
}

    /* Number Literal Token */
{DIGIT}+(\.{DIGIT}*)?{LETTER}* {
    // Since numbers in this language are comprised of a numerical value and a unit suffix, need to do some extra work
    // to parse the number literal token.

    std::string text(yytext);

    // Find the first index of the suffix part
    size_t firstLetterIndex = text.find_first_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");

    // We will always have a number part, so extract it and convert it to a double
    std::string numberPart = text.substr(0, firstLetterIndex);
    double value = std::atof(numberPart.c_str());

    // Next, extract the suffix part, if it exists
    std::string suffixPart("");
    if(firstLetterIndex != std::string::npos) {
        suffixPart = text.substr(firstLetterIndex);
    }
    
    // Finally return the token
    return shell::Parser::make_NUMBER_LITERAL(shell::Number{value, suffixPart});
}

    /* String Literal Token */
\"[^\"]*\" {
    std::string value(yytext);

    // remove the leading and trailing quotes from the string
    value = value.substr(1, value.length() - 2);

    std::cout << "Token: STRING_LITERAL \"" << value << "\"" << std::endl;

    return shell::Parser::make_STRING_LITERAL(value);
}

    /* A statment ends either with a new line or semicolon */
\n|; { 
    std::cout << "Token: STATEMENT_END" << std::endl;
    return shell::Parser::make_STATEMENT_END();
}

    /* An identifier token. These are typically used for identifying variables, functions, flags, etc.
     */
{ID_START}{ID_CHAR}* {
    std::cout << "Token: IDENTIFIER \"" << yytext << "\"" << std::endl;
    
    return shell::Parser::make_IDENTIFIER(yytext);
}

\= { return shell::Parser::make_EQUALS(); }
\( { return shell::Parser::make_LEFT_PAREN(); }
\) { return shell::Parser::make_RIGHT_PAREN(); }
\, { return shell::Parser::make_COMMA(); }

    /* Ignore the rest of the whitespace */
[\r\t ] {
    /* Ignore whitespace */
}

    /* If we get here, then we have an unknown character. This should remain the last token in the file */
. {
    std::cerr << "Lexer: Unknown Character \"" << yytext << "\"" << std::endl;
}

%%


