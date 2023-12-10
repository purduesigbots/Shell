/**
 * @file data.hpp
 * 
 * @brief Utilities surrounding data in the shell.
 */

#pragma once

#include <string>
#include <ostream>
#include <vector> 

namespace shell
{

/**
 * @brief A numerical value with an optional unit suffix.
 */
struct Number
{
    double          value;
    std::string     suffix;
};

/**
 * @brief Prints a number to the passed output stream.
 */
inline std::ostream& operator<<(std::ostream& os, const Number& num)
{
    os << num.value << num.suffix;
    return os;
}

/**
 * @brief Stores type information for a value or expression in the shell.
 */
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

        TUPLE
    };

    /// @brief The 
    int primaryType;

    /// @brief If this type is a compound type, I.E. a tuple or array, this stores the subtypes within that compound type.
    ///        For primitive types, this is an empty vector. 
    std::vector<TypeInfo> subTypes;

    /// @brief Returns whether or not this TypeInfo is a primitive type or not
    /// @return True if the type is a primitive, false otherwise. 
    bool isPrimitive() const; 

    /// @brief Returns whether or not this TypeInfo is a compound type or not.
    /// @return True if the type is a compound type, false otherwise. 
    bool isCompound() const;

    /// @brief Builds a TypeInfo object for the "number" primtitive type.
    static TypeInfo makeNumber();

    /// @brief Builds a TypeInfo object for the "string" primitive type.
    static TypeInfo makeString();
    
    /// @brief Builds a TypeInfo object for the "boolean" primitive type.
    static TypeInfo makeBoolean();

    /// @brief Builds a TypeInfo obect for an empty tuple. 
    static TypeInfo makeEmptyTuple();
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