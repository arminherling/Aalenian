#pragma once

#include "CompilerApi.h"
#include "Token.h"

enum class COMPILER_API NodeKind
{
    Unknown,
    AssignmentStatement,
    Name,
    Number
};

class COMPILER_API Node
{
public:
    Node(NodeKind kind);

    NodeKind Kind();

private:
    NodeKind m_kind;
};

class COMPILER_API Statement : public Node
{
public:
    Statement(NodeKind kind);
};

class COMPILER_API Expression : public Node
{
public:
    Expression(NodeKind kind);
};

class COMPILER_API AssignmentStatement : public Statement
{
public:
    AssignmentStatement(Expression* leftExpression, const Token& equalsToken, Expression* rightExpression);

private:
    Expression* m_leftExpression;
    Token m_equalsToken;
    Expression* m_rightExpression;
};

class COMPILER_API Name : public Expression
{
public:
    Name(const Token& token);

    [[nodiscard]] const Token& Identifier() noexcept
    {
        return m_token;
    }

private:
    Token m_token;
};

class COMPILER_API Number : public Expression
{
public:
    Number(const Token& token);

    [[nodiscard]] const Token& Literal() noexcept
    {
        return m_token;
    }

private:
    Token m_token;
};
