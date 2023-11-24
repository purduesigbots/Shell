/**
 * This file serves simply as a wapper for the header generated by Bison.
 * This way, if the name of the generated header changes, we only need to change 
 * it in one place.
 */

#pragma once

#include <optional>

#include "shell/parser/parser.y.hpp"
#include "shell/ast/ast.hpp"

namespace shell {

    class Parser : public yyBisonParser
    {
    public:
        Parser(shell::Lexer& _lexer)
        : yyBisonParser(_lexer, *this)
        {

        }

        /**
         * @brief Parses the next statement in the input stream.
         */
        // TODO: Implement
        std::optional<AstNode> parseNextStatement();

        /**
         * @brief Parses the input stream until the end of the file
         */
        // TODO: Implement
        std::optional<AstNode> parseFile();
        
        friend class yyBisonParser;

    protected:
        bool                    stopAfterStatement = false;
        std::optional<AstNode>  result = std::nullopt;
    };

} // namespace shell
