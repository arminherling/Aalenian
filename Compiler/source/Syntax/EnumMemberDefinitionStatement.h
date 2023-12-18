#pragma once

#include <Defines.h>
#include <Syntax/Statement.h>
#include <Syntax/Name.h>
#include <Syntax/Token.h>
#include <Syntax/Number.h>

class COMPILER_API EnumMemberDefinitionStatement : public Statement
{
public:
    EnumMemberDefinitionStatement(Name* name);
    EnumMemberDefinitionStatement(
        Name* name, 
        const Token& equal, 
        Number* value);

    [[nodiscard]] Name* name() noexcept { return m_name; }
    [[nodiscard]] const std::optional<Token>& equal() noexcept { return m_equal; }
    [[nodiscard]] const std::optional<Number*>& value() noexcept { return m_value; }

private:
    Name* m_name;
    std::optional<Token> m_equal;
    std::optional<Number*> m_value;
};
