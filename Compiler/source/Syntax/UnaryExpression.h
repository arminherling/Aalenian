#pragma once

#include <Defines.h>
#include <Syntax/Expression.h>
#include <Syntax/Token.h>

class COMPILER_API UnaryExpression : public Expression
{
public:
    UnaryExpression(
        const Token& unaryOperator, 
        Expression* expression);

    [[nodiscard]] const Token& unaryOperator() noexcept { return m_unaryOperator; }
    [[nodiscard]] Expression* expression() noexcept { return m_expression; }

private:
    Token m_unaryOperator;
    Expression* m_expression;
};
