#pragma once

#include <Defines.h>
#include <Syntax/Expression.h>
#include <Syntax/Token.h>
#include <Syntax/Type.h>

class COMPILER_API Number : public Expression
{
public:
    Number(const Token& token);
    Number(
        const Token& token, 
        const Token& colon, 
        const Type& type);

    [[nodiscard]] const Token& token() noexcept { return m_token; }
    [[nodiscard]] const std::optional<Token>& colon() noexcept { return m_colon; }
    [[nodiscard]] const std::optional<Type>& type() noexcept { return m_type; }

private:
    Token m_token;
    std::optional<Token> m_colon;
    std::optional<Type> m_type;
};
