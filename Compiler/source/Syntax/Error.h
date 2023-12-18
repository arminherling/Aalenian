#pragma once

#include <Defines.h>
#include <Syntax/Expression.h>
#include <Syntax/Token.h>

class COMPILER_API Error : public Expression
{
public:
    Error(const Token& token);

    [[nodiscard]] const Token& token() noexcept { return m_token; }

private:
    Token m_token;
};
