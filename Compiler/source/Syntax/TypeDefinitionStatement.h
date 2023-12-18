#pragma once

#include <Defines.h>
#include <Syntax/Block.h>
#include <Syntax/Statement.h>
#include <Syntax/Token.h>

class COMPILER_API TypeDefinitionStatement : public Statement
{
public:
    TypeDefinitionStatement(
        const Token& keyword, 
        const Token& name, 
        Block* body);

    [[nodiscard]] const Token& keyword() noexcept { return m_keyword; }
    [[nodiscard]] const Token& name() noexcept { return m_name; }
    [[nodiscard]] Block* body() noexcept { return m_body; }

private:
    Token m_keyword;
    Token m_name;
    Block* m_body;
};
