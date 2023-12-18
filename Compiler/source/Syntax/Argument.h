#pragma once

#include <Defines.h>
#include <Syntax/Expression.h>
#include <Syntax/Node.h>
#include <Syntax/Token.h>

class COMPILER_API Argument : public Node
{
public:
    Argument(
        const std::optional<Token>& ref, 
        Expression* expression);

    [[nodiscard]] const std::optional<Token>& ref() const noexcept { return m_ref; }
    [[nodiscard]] bool isReference() const noexcept { return m_ref.has_value(); }
    [[nodiscard]] Expression* expression() const noexcept { return m_expression; }

private:
    std::optional<Token> m_ref;
    Expression* m_expression;
};
