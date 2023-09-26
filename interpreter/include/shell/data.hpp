#pragma once

#include <vector>

struct TypeInfo
{
    enum 
    {
        NUMBER,
        STRING,
        BOOL,
        TUPLE,
    } type;

    std::vector<TypeInfo> subTypes; 

    bool isNumber() const { return type == NUMBER; }
    bool isString() const { return type == STRING; }
    bool isBool()   const { return type == BOOL; }

    bool isPrimitive() const { return isNumber() || isString() || isBool(); }
    bool isCompound()  const { return type == TUPLE; }

    bool operator= (TypeInfo &o) const {
        return type == o.type && 
    }
};

/**
 * @brief      Represents the type of a variable or argument
 */
struct TypeInfo
{
    enum
    {
        NUMBER,
        STRING 
    }
};


