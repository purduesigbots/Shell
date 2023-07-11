#include "shell/shell.hpp"

namespace shell {

Shell::Shell()
{
    
}

Shell::~Shell()
{
    
}

void Shell::run(std::istream& input, std::ostream& output, std::ostream& error)
{

}

void Shell::setPrompt(std::string prompt)
{
    _prompt = prompt;
}

} // namespace shell