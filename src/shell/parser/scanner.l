
%{
#include <stdio.h>

#include "shell/parser/parser.y.hpp"

%}

%option c++

%option nodefault
%option noyywrap
%option yyclass="Scanner"
%option prefix="Shell_"

digit           [0-9]
letter          [a-zA-Z]
idStart         [a-zA-Z_]
idChar          [a-zA-Z0-9_]

%%

\n|\;           {                
    return *yytext;
}

\=                   { 
    printf("EQUALS\n");
    return *yytext;
}

    /* Identifier: Starts with a letter or underscore, and then contains any number of letters, numbers, or underscores 
     * until the next whitespace character.
     */
{idStart}{idChar}*  { 
    printf("IDENTIFIER: \"%s\"\n", yytext); 
    return IDENTIFIER;
}

{digit}+(\.{digit}*)?{letter}* {
    printf("NUMBER: \"%s\"\n", yytext);
    return NUMBER_LITERAL;
}

\"[^"]*\" {
    printf("STRING: \"%s\"\n", yytext);
    return STRING_LITERAL;
}

    /* Variable evaluation. This is handled in the scanner since there can be no whitespace between the dollar sign
     * and the variable name.
     */
\${idStart}{idChar}* {
    printf("VARIABLE_REF: \"%s\"\n", yytext);
    return VARIABLE_REF;
}

    /* Eat up spaces and tabs left in the input */
[ \t]              ;

    /* Unexpected token */
. {
    printf("ERROR: Unexpected token \"%s\"\n", yytext);
}

%%