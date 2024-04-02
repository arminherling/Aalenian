#pragma once

#include <Defines.h>
#include <Syntax/Expression.h>
#include <Syntax/Token.h>

enum class UnaryOperatornKind
{
    Invalid,
    Negation,
};

class COMPILER_API UnaryExpression : public Expression
{
public:
    UnaryExpression(
        const Token& unaryOperatorToken,
        UnaryOperatornKind unaryOperator,
        Expression* expression);

    [[nodiscard]] const Token& unaryOperatorToken() noexcept { return m_unaryOperatorToken; }
    [[nodiscard]] UnaryOperatornKind unaryOperator() noexcept { return m_unaryOperator; }
    [[nodiscard]] Expression* expression() noexcept { return m_expression; }

private:
    Token m_unaryOperatorToken;
    UnaryOperatornKind m_unaryOperator;
    Expression* m_expression;
};

COMPILER_API QString StringifyUnaryOperation(UnaryOperatornKind kind);
