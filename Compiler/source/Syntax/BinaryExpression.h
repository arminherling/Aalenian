#pragma once

#include <Defines.h>
#include <Syntax/Expression.h>
#include <Syntax/Token.h>

enum class BinaryOperatornKind
{
    Invalid,
    ScopeAccess,
    MemberAccess,
    Addition,
    Subtraction,
    Multiplication,
    Division,
};

class COMPILER_API BinaryExpression : public Expression
{
public:
    BinaryExpression(
        Expression* leftExpression, 
        const Token& binaryOperatorToken,
        BinaryOperatornKind binaryOperator,
        Expression* rightExpression);

    [[nodiscard]] Expression* leftExpression() noexcept { return m_leftExpression; }
    [[nodiscard]] const Token& binaryOperatorToken() noexcept { return m_binaryOperatorToken; }
    [[nodiscard]] BinaryOperatornKind binaryOperator() noexcept { return m_binaryOperator; }
    [[nodiscard]] Expression* rightExpression() noexcept { return m_rightExpression; }

private:
    Expression* m_leftExpression;
    Token m_binaryOperatorToken;
    BinaryOperatornKind m_binaryOperator;
    Expression* m_rightExpression;
};

COMPILER_API QString StringifyBinaryOperation(BinaryOperatornKind kind);
