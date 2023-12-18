#pragma once

#include <Syntax/Token.h>
#include <Syntax/Expression.h>

class COMPILER_API Name : public Expression
{
public:
    Name(const Token& token);

    [[nodiscard]] const Token& identifier() noexcept { return m_token; }

private:
    Token m_token;
};
