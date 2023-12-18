#pragma once

#include <Defines.h>
#include <Syntax/Expression.h>
#include <Syntax/Token.h>

class COMPILER_API ScopeAccess : public Expression
{
public:
    ScopeAccess(
        const Token& doubleColon, 
        Expression* expression);

    [[nodiscard]] const Token& doubleColon() noexcept { return m_doubleColon; }
    [[nodiscard]] Expression* expression() noexcept { return m_expression; }

private:
    Token m_doubleColon;
    Expression* m_expression;
};
