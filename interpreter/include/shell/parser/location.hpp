#pragma once

#include <ostream>

namespace shell {

struct Position
{
    const char* filename;
    int column = 0;
    int line = 0; 
};

struct Location
{
    Position    begin;
    Position    end;

    static inline Location join(Location start, Location end)
    {
        return Location{start.begin, end.end};
    }
};

inline std::ostream& operator<<(std::ostream& stream, const Location& loc)
{
    return stream << "(" << loc.begin.line << ":" << loc.begin.column 
        <<  " - " << loc.end.line << ":" << loc.end.column << ")";
}

} // namespace shell
