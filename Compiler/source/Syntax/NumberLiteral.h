#pragma once

#include <Defines.h>
#include <Syntax/Expression.h>
#include <Syntax/Token.h>
#include <Syntax/TypeNode.h>

class COMPILER_API NumberLiteral : public Expression
{
public:
    NumberLiteral(const Token& token);
    NumberLiteral(
        const Token& token, 
        const Token& colon, 
        const TypeNode& type);

    [[nodiscard]] const Token& token() noexcept { return m_token; }
    [[nodiscard]] const std::optional<Token>& colon() noexcept { return m_colon; }
    [[nodiscard]] const std::optional<TypeNode>& type() noexcept { return m_type; }

private:
    Token m_token;
    std::optional<Token> m_colon;
    std::optional<TypeNode> m_type;
};
