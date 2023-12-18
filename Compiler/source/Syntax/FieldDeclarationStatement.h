#pragma once

#include <Defines.h>
#include <Syntax/Statement.h>
#include <Syntax/Name.h>
#include <Syntax/Type.h>
#include <Syntax/Expression.h>

class COMPILER_API FieldDeclarationStatement : public Statement
{
public:
    FieldDeclarationStatement(
        Name* name,
        const std::optional<Token>& colon,
        const std::optional<Type>& type,
        const std::optional<Token>& equals,
        const std::optional<Expression*>& expression);

    [[nodiscard]] Name* name() noexcept { return m_name; }
    [[nodiscard]] const std::optional<Token>& colon() noexcept { return m_colon; }
    [[nodiscard]] const std::optional<Type>& type() noexcept { return m_type; }
    [[nodiscard]] const std::optional<Token>& equals() noexcept { return m_equals; }
    [[nodiscard]] const std::optional<Expression*>& expression() noexcept { return m_expression; }

private:
    Name* m_name;
    std::optional<Token> m_colon;
    std::optional<Type> m_type;
    std::optional<Token> m_equals;
    std::optional<Expression*> m_expression;
};
