#pragma once

#include <string>

#include "shell/ast/ast_node.hpp"
#include "shell/types.hpp"

namespace shell
{

class Expression : public AstNode
{
public:
    Expression() {}
    ~Expression() {}

private:

};

class TupleExpression : public Expression
{
public:

private:
    std::vector<Expression> expressions;
};

class StringLiteral : public Expression, public std::string
{
public:

    StringLiteral(std::string value) : std::string(value) {

    }

private:

};

class NumberLiteral : public Expression
{
public:
    NumberLiteral(Number value) {

    }
};

class BoolLiteral : public Expression
{
public:
    BoolLiteral(bool value) {

    }
};

} // namespace shell