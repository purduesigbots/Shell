#include "shell/parser/parser.hpp"

#include <optional>

#include "shell/ast/ast.hpp"

namespace shell {

std::optional<AstNode> Parser::parseNextStatement()
{
    //std::cout << "\nPARSING STATEMENT. Enter your input: " << std::endl;

    stopAfterStatement = true;

    if(parse() == 0) {
       // std::cout << "\nPARSE VALID. Resulting tree:\n" << std::endl;

        return result;
    }

    std::cout << "PARSE INVALID" << std::endl;

    return std::nullopt;
}

std::optional<AstNode> Parser::parseFile()
{
    stopAfterStatement = false;

    return std::nullopt;
}

} // namespace shell