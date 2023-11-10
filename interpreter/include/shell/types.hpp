#pragma once

#include <string>
#include <ostream>

namespace shell
{

struct Number
{
    double          value;
    std::string     suffix;
};

inline std::ostream& operator<<(std::ostream& os, const Number& num)
{
    os << num.value << num.suffix;
    return os;
}


} // namespace shell