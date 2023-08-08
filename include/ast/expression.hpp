#pragma once

#include <string>

namespace shell
{

class Expression
{
public:
    Expression();
    ~Expression();

private:

};

class StringLiteral : public Expression, public std::string
{
public:

private:

};

class IntegerLiteral : public Expression
{

};

class BoolLiteral : public Expression
{

};

} // namespace shell