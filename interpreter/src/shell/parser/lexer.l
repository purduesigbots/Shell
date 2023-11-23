    /*
     * lexer.l
     *
     * This file contains the lexer (aka tokenizer) for this language. The functionality here gets exported to the
     * Lexer class after Flex compiles this program.
     */

     
    //==================================================================================================================
    // SETTINGS FOR FLEX
    // These directives instruct flex how to generate the Lexer. 
    //==================================================================================================================

    // Tell Flex that we want to generate the lexer as a C++ class.
%option c++

%option noyywrap

    // We do not want Flex to generate a default rule for us. Any token that is not matched by one of the rules below is
    // considered an error.
%option nodefault

    // Tell Flex the name of the class to generate, as well as a prefix to give to the class. 
%option yyclass="Lexer"
%option prefix="shell_"

    //==================================================================================================================
    // CODE INSERTION BLOCKS
    //==================================================================================================================
%{
    #include <iostream>
    #include <cstdlib>
    #include "shell/parser/lexer.hpp"
    #include "shell/parser/parser.hpp"

    #include "shell/data.hpp"

    // YY_USER_ACTION is called whenever a rule is matched, and we redefine it here to update the current location of
    // the scanning stream. 
    #define YY_USER_ACTION updateLocation(yyleng, yytext);

    // Since we are using variants for storing the values of tokens, we need to define yyterminate() to return a
    // specific token. Otherwise, Flex will return 0 as a int, causing type errors to occur. 
    #define yyterminate() shell::Parser::make_END(_currentLocation);
%}

    //==================================================================================================================
    // REGULAR DEFINITIONS
    // These are names for regular expressions used throughout the Lexer. These make the regular expressions for each
    // each token more readable.
    //==================================================================================================================

DIGIT       [0-9]
ID_START    [a-zA-Z_]
ID_CHAR     [a-zA-Z0-9_]
LETTER      [a-zA-Z]


%%
    //==================================================================================================================
    // LEXER RULES
    // These are the rules that Flex uses to generate the Lexer. Each rule is comprised of a regular expression and a 
    // body of C++ code that executes when the specific token is found. Some rules simply create a token and return it
    // while others do additional processing and extract extra information from the input. 
    //==================================================================================================================    

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
    return shell::Parser::make_NUMBER_LITERAL(shell::Number{value, suffixPart}, _currentLocation);
}

    /* String Literal Token */
\"[^\"]*\" {
    std::string value(yytext);

    // remove the leading and trailing quotes from the string
    value = value.substr(1, value.length() - 2);

    std::cout << "Token: STRING_LITERAL \"" << value << "\"" << std::endl;

    return shell::Parser::make_STRING_LITERAL(value, _currentLocation);
}

    /* A statment ends either with a new line or semicolon */
\n|; { 
    std::cout << "Token: STATEMENT_END" << std::endl;
    return shell::Parser::make_STATEMENT_END(_currentLocation);
}

    /* An identifier token. These are typically used for identifying variables, functions, flags, etc.
     */
{ID_START}{ID_CHAR}* {
    std::cout << "Token: IDENTIFIER \"" << yytext << "\"" << std::endl;
    
    return shell::Parser::make_IDENTIFIER(yytext, _currentLocation);
}

\= { return shell::Parser::make_EQUALS(_currentLocation); }
\( { return shell::Parser::make_LEFT_PAREN(_currentLocation); }
\) { return shell::Parser::make_RIGHT_PAREN(_currentLocation); }
\, { return shell::Parser::make_COMMA(_currentLocation); }

    /* Ignore the rest of the whitespace */
[\r\t ] {
    /* Ignore whitespace */
}

    /* If we get here, then we have an unknown character. This should remain the last token in the file */
. {
    std::cerr << "Lexer: Unknown Character \"" << yytext << "\"" << std::endl;
}

%%

namespace shell {
    // This function is called to update the location of the current parsing stream.
    void Lexer::updateLocation(int length, const char* text)
    {
        // First, update the starting location to match the end of the previous token.
        _currentLocation.begin.line = _currentLocation.end.line;
        _currentLocation.begin.column = _currentLocation.end.column;

        // Next we scan the input text and update the end location. If we reach a newline, we increment the line
        // number and reset the column number. Otherwise, we just increment the column number.
        for(int i = 0; text[i] != '\0'; i++) {
            if(text[i] == '\n') {
                _currentLocation.end.line++;
                _currentLocation.end.column = 0;
            } else {
                _currentLocation.end.column++;
            }
        }
    }

} // namespace shell
