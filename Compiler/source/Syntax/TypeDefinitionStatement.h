#pragma once

#include <Defines.h>
#include <Syntax/BlockNode.h>
#include <Syntax/Statement.h>
#include <Syntax/Token.h>

class COMPILER_API TypeDefinitionStatement : public Statement
{
public:
    TypeDefinitionStatement(
        const Token& keyword, 
        const Token& name, 
        BlockNode* body);

    [[nodiscard]] const Token& keyword() noexcept { return m_keyword; }
    [[nodiscard]] const Token& name() noexcept { return m_name; }
    [[nodiscard]] BlockNode* body() noexcept { return m_body; }

private:
    Token m_keyword;
    Token m_name;
    BlockNode* m_body;
};
