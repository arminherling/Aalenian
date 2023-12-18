#pragma once

#include <Defines.h>
#include <Syntax/Statement.h>
#include <Syntax/NameExpression.h>
#include <Syntax/TypeNode.h>
#include <Syntax/Expression.h>

class COMPILER_API FieldDeclarationStatement : public Statement
{
public:
    FieldDeclarationStatement(
        NameExpression* name,
        const std::optional<Token>& colon,
        const std::optional<TypeNode>& type,
        const std::optional<Token>& equals,
        const std::optional<Expression*>& expression);

    [[nodiscard]] NameExpression* name() noexcept { return m_name; }
    [[nodiscard]] const std::optional<Token>& colon() noexcept { return m_colon; }
    [[nodiscard]] const std::optional<TypeNode>& type() noexcept { return m_type; }
    [[nodiscard]] const std::optional<Token>& equals() noexcept { return m_equals; }
    [[nodiscard]] const std::optional<Expression*>& expression() noexcept { return m_expression; }

private:
    NameExpression* m_name;
    std::optional<Token> m_colon;
    std::optional<TypeNode> m_type;
    std::optional<Token> m_equals;
    std::optional<Expression*> m_expression;
};
