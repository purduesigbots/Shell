#include "shell/data.hpp"

namespace shell {

bool TypeInfo::isPrimitive() const
{
    return primaryType >= NUMBER &&
        primaryType <= BOOLEAN
        ;
}

bool TypeInfo::isCompound() const 
{
    return primaryType == TUPLE
    ;
};

TypeInfo TypeInfo::makeNumber()
{
    TypeInfo newTypeInfo;

    newTypeInfo.primaryType = NUMBER;

    return newTypeInfo;
}

TypeInfo TypeInfo::makeString()
{
    TypeInfo newTypeInfo;

    newTypeInfo.primaryType = STRING;

    return newTypeInfo;
}

TypeInfo TypeInfo::makeBoolean()
{
    TypeInfo newTypeInfo;

    newTypeInfo.primaryType = BOOLEAN;

    return newTypeInfo;
}

TypeInfo TypeInfo::makeEmptyTuple()
{
    TypeInfo newTypeInfo;
    
    newTypeInfo.primaryType = TUPLE;

    return newTypeInfo;
}


} // namespace shell