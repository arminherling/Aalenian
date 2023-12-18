#pragma once

#include <Defines.h>
#include <Syntax/Expression.h>
#include <Syntax/Statement.h>

class COMPILER_API ExpressionStatement : public Statement
{
public:
    ExpressionStatement(Expression* expression);

    [[nodiscard]] Expression* expression() noexcept { return m_expression; }

private:
    Expression* m_expression;
};
