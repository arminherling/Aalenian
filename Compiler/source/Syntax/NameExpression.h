#pragma once

#include <Syntax/Token.h>
#include <Syntax/Expression.h>

class COMPILER_API NameExpression : public Expression
{
public:
    NameExpression(const Token& token);

    [[nodiscard]] const Token& identifier() noexcept { return m_token; }

private:
    Token m_token;
};
