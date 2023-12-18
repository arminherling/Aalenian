#pragma once

#include <Defines.h>
#include <Syntax/Expression.h>
#include <Syntax/Token.h>

class COMPILER_API BinaryExpression : public Expression
{
public:
    BinaryExpression(
        Expression* leftExpression, 
        const Token& binaryOperator, 
        Expression* rightExpression);

    [[nodiscard]] Expression* leftExpression() noexcept { return m_leftExpression; }
    [[nodiscard]] const Token& binaryOperator() noexcept { return m_binaryOperator; }
    [[nodiscard]] Expression* rightExpression() noexcept { return m_rightExpression; }

private:
    Expression* m_leftExpression;
    Token m_binaryOperator;
    Expression* m_rightExpression;
};
