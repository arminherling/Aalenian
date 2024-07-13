#pragma once

#include <Compiler/API.h>
#include <Syntax/Expression.h>
#include <Syntax/Token.h>

class COMPILER_API GroupingExpression : public Expression
{
public:
    GroupingExpression(
        const Token& openParenthesis, 
        Expression* expression, 
        const Token& closeParenthesis);

    [[nodiscard]] const Token& openParenthesis() const noexcept { return m_openParenthesis; }
    [[nodiscard]] Expression* expression() const noexcept { return m_expression; }
    [[nodiscard]] const Token& closeParenthesis() const noexcept { return m_closeParenthesis; }

private:
    Token m_openParenthesis;
    Expression* m_expression;
    Token m_closeParenthesis;
};
