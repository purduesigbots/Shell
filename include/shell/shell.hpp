#pragma once

#include <stdio.h>
#include <iostream>
#include <map>
#include <string>

namespace shell {

class Shell
{
public:

    Shell();
    ~Shell();

    void run(std::istream& input = std::cin, std::ostream& output = std::cout, std::ostream& error = std::cerr);

    void setPrompt(std::string prompt);

private:
    std::string                     _prompt;
    std::map<std::string, void*>    _commands;

};

} // namespace shell