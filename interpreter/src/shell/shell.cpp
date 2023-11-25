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
    while(true) {
        output << "shell $>  ";

        std::optional<AstNode> astOptional = _parser.parseNextStatement();

        if(!astOptional)
            break;
        
        AstNode astTree = astOptional.value();

        //astTree.print(output);

        //output << "\nExecuting entered input:\n" << std::endl;

        // Execute the command.
        // TODO: This will need moved and made more safe eventually
        std::string commandName = astTree.getStringValue();

        if(auto search = _commands.find(commandName); search != _commands.end()) {
            CommandCallback cb = search->second;

            CommandArgs args;
            args._name = commandName;

            // Build command helper based on ast
            for(AstNode child : astTree.children()) {
                if(child.type() == AstNode::COMMAND_UNNAMED_ARG) {
                    
                }
                else if(child.type() == AstNode::COMMAND_NAMED_ARG) {
                    std::string name = child.getStringValue();

                    AstNode subChild = child.children()[0];

                    switch(subChild.type()) 
                    {
                    case AstNode::NUMBER_LITERAL:
                        args.addNamedNumber(name, subChild.getNumberValue());
                        break;

                    case AstNode::STRING_LITERAL:
                        args.addNamedString(name, subChild.getStringValue());
                        break;

                    case AstNode::BOOLEAN_LITERAL:
                        args.addNamedBoolean(name, subChild.getBooleanValue());
                        break;
                    }
                }
            }

            cb(args);
        }
        else {
            error << "Command \"" << commandName << "\" not found";

            continue;
        }
    }

    std::cerr << "EOF" << std::endl;
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