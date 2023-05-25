#pragma once

#include <stdio.h>
#include <iostream>

namespace legs::shell {

typedef bool(*CommandCallback)();

bool runProgram(std::istream& sourceStream = std::cin);

bool addCommand(std::string name, CommandCallback callback);

} // namespace legs::shell