#pragma once

#include <Defines.h>
#include <Syntax/Statement.h>
#include <Syntax/Token.h>
#include <Syntax/ParametersNode.h>
#include <Syntax/BlockNode.h>

class COMPILER_API FunctionDefinitionStatement : public Statement
{
public:
    FunctionDefinitionStatement(
        const Token& keyword, 
        const Token& name, 
        ParametersNode* parameters,
        BlockNode* body);

    [[nodiscard]] const Token& keyword() noexcept { return m_keyword; }
    [[nodiscard]] const Token& name() noexcept { return m_name; }
    [[nodiscard]] ParametersNode* parameters()  noexcept { return m_parameters; }
    [[nodiscard]] BlockNode* body() noexcept { return m_body; }

private:
    Token m_keyword;
    Token m_name;
    ParametersNode* m_parameters;
    BlockNode* m_body;
};
