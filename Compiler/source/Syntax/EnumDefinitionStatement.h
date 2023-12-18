#pragma once

#include <Defines.h>
#include <Syntax/BlockNode.h>
#include <Syntax/Statement.h>
#include <Syntax/Token.h>
#include <Syntax/Type.h>

class COMPILER_API EnumDefinitionStatement : public Statement
{
public:
    EnumDefinitionStatement(
        const Token& keyword,
        const Token& name,
        const std::optional<Type>& type,
        BlockNode* body);

    [[nodiscard]] const Token& keyword() noexcept { return m_keyword; }
    [[nodiscard]] const Token& name() noexcept { return m_name; }
    [[nodiscard]] const std::optional<Type>& baseType() noexcept { return m_baseType; }
    [[nodiscard]] BlockNode* body() noexcept { return m_body; }

private:
    Token m_keyword;
    Token m_name;
    std::optional<Type> m_baseType;
    BlockNode* m_body;
};
