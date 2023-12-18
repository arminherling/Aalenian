#pragma once

#include <Defines.h>
#include <Syntax/Statement.h>
#include <Syntax/Token.h>
#include <Syntax/Parameters.h>
#include <Syntax/BlockNode.h>

class COMPILER_API MethodDefinitionStatement : public Statement
{
public:
    MethodDefinitionStatement(
        const Token& keyword, 
        const Token& name, 
        Parameters* parameters, 
        BlockNode* body);

    [[nodiscard]] const Token& keyword() noexcept { return m_keyword; }
    [[nodiscard]] const Token& name() noexcept { return m_name; }
    [[nodiscard]] Parameters* parameters()  noexcept { return m_parameters; }
    [[nodiscard]] BlockNode* body() noexcept { return m_body; }

private:
    Token m_keyword;
    Token m_name;
    Parameters* m_parameters;
    BlockNode* m_body;
};
