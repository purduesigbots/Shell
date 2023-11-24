# Shell - Architecture


## Class Structure

```mermaid
classDiagram

class Shell

class yyBisonParser

class Parser

class yyFlexLexer

class Lexer


yyBisonParser <|-- Parser
yyFlexLexer <|-- Lexer


Shell *-- Parser
Shell *-- Lexer


```