#pragma once

#include <Defines.h>
#include <Syntax/Statement.h>
#include <Syntax/Expression.h>
#include <Syntax/Token.h>

class COMPILER_API AssignmentStatement : public Statement
{
public:
    AssignmentStatement(
        Expression* leftExpression, 
        const Token& equalsToken, 
        Expression* rightExpression);

    [[nodiscard]] Expression* leftExpression() noexcept { return m_leftExpression; }
    [[nodiscard]] Expression* rightExpression() noexcept { return m_rightExpression; }

private:
    Expression* m_leftExpression;
    Token m_equalsToken;
    Expression* m_rightExpression;
};
