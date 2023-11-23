#include "shell/shell.hpp"

#include "shell/parser/parser.hpp"
#include "shell/parser/lexer.hpp"

namespace shell {

Shell::Shell()
: _lexer(), _parser(_lexer)
{
    
}

Shell::~Shell()
{
    
}

void Shell::runInteractive(std::istream& input, std::ostream& output, std::ostream& error)
{
    while(auto astOptional = _parser.parseNextStatement()) {
        AstNode astTree = astOptional.value();

        astTree.print(output);
    }
}

void Shell::setPrompt(std::string prompt)
{
    _prompt = prompt;
}

void Shell::registerCommand(std::string name, CommandCallback callback)
{
    _commands.insert(std::make_pair(name, callback));
}

} // namespace shell