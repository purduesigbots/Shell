#pragma once

#include <ostream>

namespace shell {

/**
 * @brief Represents a single point within a file
 */
struct Position
{
    const char* filename;
    int column = 0;
    int line = 0; 
};

/**
 * @brief Represents an area of text that a definition or expression resides in within an input stream. 
 */
struct Location
{
    Position    begin;
    Position    end;

    static inline Location join(Location start, Location end)
    {
        return Location{start.begin, end.end};
    }
};

/**
 * @brief Prints the passed location to the passed output stream. 
 */
inline std::ostream& operator<<(std::ostream& stream, const Location& loc)
{
    return stream << "(" << loc.begin.line << ":" << loc.begin.column 
        <<  " - " << loc.end.line << ":" << loc.end.column << ")";
}

} // namespace shell
