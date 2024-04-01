#pragma once

#include <Defines.h>
#include <Syntax/Statement.h>
#include <Syntax/NameExpression.h>
#include <Syntax/Token.h>
#include <Syntax/NumberLiteral.h>

class COMPILER_API EnumFieldDefinitionStatement : public Statement
{
public:
    EnumFieldDefinitionStatement(NameExpression* name);
    EnumFieldDefinitionStatement(
        NameExpression* name,
        const Token& equal, 
        NumberLiteral* value);

    [[nodiscard]] NameExpression* name() noexcept { return m_name; }
    [[nodiscard]] const std::optional<Token>& equal() noexcept { return m_equal; }
    [[nodiscard]] const std::optional<NumberLiteral*>& value() noexcept { return m_value; }

private:
    NameExpression* m_name;
    std::optional<Token> m_equal;
    std::optional<NumberLiteral*> m_value;
};
