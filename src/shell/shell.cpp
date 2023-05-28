#include "shell/shell.hpp"

#include <istream>
#include <cstdio>
#include <map>
#include <string>

#include "shell/parser.hpp"
#include "shell/tokenizer.hpp"
#include "shell/command_args.hpp"

#include "string"

namespace shell {

std::map<std::string, CommandCallback> commands;

void Shell::parseNamedArgument(Tokenizer& tokenizer, CommandArgs& args)
{
    std::string name = tokenizer.next().strValue;

    // If the next token is not an equals sign, we have a flag argument
    if(tokenizer.peek().getType() != Token::TYPE_DELIMITER && tokenizer.peek().chrValue != '=') {
        args.addFlag(name);
        return;
    }

    // Eat the equals sign 
    tokenizer.next();

    if(tokenizer.peek().getType() == Token::TYPE_STRING) {
        Token tokString = tokenizer.next();
        args.addString(name, tokString.strValue);
        return;
    }

    if(tokenizer.peek().getType() == Token::TYPE_NUMBER) {
        Token tokNumber = tokenizer.next();
        args.addNumber(name, tokNumber.fltValue, tokNumber.strValue);
        return;
    }
}

void Shell::parseCommandArguments(Tokenizer& tokenizer, CommandArgs& args)
{
    while(tokenizer.peek().getType() != Token::TYPE_END_OF_STATEMENT) {
        if(tokenizer.peek().getType() == Token::TYPE_IDENTIFIER) {
            parseNamedArgument(tokenizer, args);
        } else {
            // Todo: Parse unnamed arguments
        }
    }
}

void Shell::parseCommand(Tokenizer& tokenizer)
{
    if(tokenizer.peek().getType() == Token::TYPE_END_OF_STATEMENT) {
        tokenizer.next();
        return;
    }

    if(tokenizer.peek().getType() != Token::TYPE_IDENTIFIER) {
        std::cout << "Tokenizer Error: Expected an identifier" << std::endl;
        return;
    }

    Token tokCmd = tokenizer.next();
    std::string commandName = tokCmd.strValue;


    // TODO: Command parsing
    CommandArgs args;
    args.name = commandName;
    parseCommandArguments(tokenizer, args);

    // Accept the end of statement token;
    if(tokenizer.next().getType() != Token::TYPE_END_OF_STATEMENT) {
        std::cout << "Parsing Error: Expected end of statement after a command line\n";
        return;
    }

    if(!commands.contains(commandName)) {
        std::cout << "Command \"" << commandName << "\" not found" << std::endl;
        return;
    }

    CommandCallback commandCallback = commands.at(commandName);
    commandCallback(args);
}

void Shell::parseStatement(Tokenizer& tokenizer)
{
    parseCommand(tokenizer);
}

bool Shell::runInteractive(std::istream& sourceStream)
{
    std::cout << "Starting program" << std::endl;

    try {
        Tokenizer tokenizer = Tokenizer(sourceStream);
        
        while(tokenizer.hasNext()) {
            parseStatement(tokenizer);
        }
    }
    catch(std::string e) {
        std::cout << e << std::endl;
        return false;
    }
    catch(...) {
        std::cout << "Unknown error" << std::endl;
        return false;
    }
    
    std::cout << "Ending program" << std::endl;

    return true;
}

bool Shell::addCommand(std::string name, CommandCallback callback)
{
    if(callback == nullptr) {
        return false;
    }

    commands[name] = callback;

    return true;
}


} // namespace shell