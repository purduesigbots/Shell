#ifndef LEXER_HPP_INCLUDED
#define LEXER_HPP_INCLUDED

// If yyFlexLexerOnce is not defined, then we need to undefine yyFlexLexer and define it to our own lexer class.
// This is done to avoid name conflicts if multiple lexers are added to the same project.
#if !defined(yyFlexLexerOnce)
    #undef yyFlexLexer
    #define yyFlexLexer shell_FlexLexer
    #include <FlexLexer.h>
#endif

#undef YY_DECL
#define YY_DECL shell::Parser::symbol_type shell::Lexer::get_next_token()

#include "shell/parser/parser.hpp"

namespace shell {

    class Shell;

    /// @brief The scanner class for the shell.
    /// @details This class is responsible for scanning and analyzing the input to brreak it into tokens and extract
    ///          other relevant information. The implementation for this class is generated 
    class Lexer : public yyFlexLexer
    {
    public:
        Lexer(Shell& driver) : _driver(driver) {}

        virtual ~Lexer() {}

        /// @brief Returns the next token from the input stream.
        /// @return The token
        virtual shell::Parser::symbol_type get_next_token();

        /// @brief Updates the current location of the scanning stream
        /// @param length The length of the text to be added to the current location.
        /// @param text  The scanned text
        void updateLocation(int length, const char* text);

    private:
        shell::location _currentLocation;

        Shell& _driver;
    };

} // namespace shell


#include "shell/shell.hpp"

#endif//LEXER_HPP_INCLUDED