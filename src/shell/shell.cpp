#include "shell/shell.hpp"

namespace shell {

Shell::Shell()
: _lexer(*this), _parser(_lexer, *this)
{
    
}

Shell::~Shell()
{
    
}

void Shell::runInteractive(std::istream& input, std::ostream& output, std::ostream& error)
{
    
}

void Shell::setPrompt(std::string prompt)
{
    _prompt = prompt;
}

} // namespace shell