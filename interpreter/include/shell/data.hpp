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

struct TypeInfo
{
    enum
    {
        NONE,
        INVALID, 

        // PRIMITIVE TYPES
        NUMBER,
        STRING,
        BOOLEAN,

        // COMPOUND TYPES
        TUPLE
    };

    int primaryType;

    bool isPrimitive() const; 

    bool isCompound() const;

    static TypeInfo makeNumber();
    static TypeInfo makeString();
    static TypeInfo makeBoolean();
};

union ValueUnion
{
    bool            booleanValue;
    Number          numberValue;
    std::string     stringValue;
};

struct Value
{

};


} // namespace shell