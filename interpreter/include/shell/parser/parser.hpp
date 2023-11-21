/**
 * This file serves simply as a wapper for the header generated by Bison.
 * This way, if the name of the generated header changes, we only need to change 
 * it in one place.
 */

#pragma once

#include "shell/parser/parser.y.hpp"

namespace shell {

    class Parser : public yyBisonParser
    {
    public:
        Parser(shell::Lexer& _lexer, shell::Shell& _shell)
        : yyBisonParser(_lexer, _shell)
        {

        }

        void parseNextLine() {}

        void parseProgram() {}
    };

} // namespace shell
