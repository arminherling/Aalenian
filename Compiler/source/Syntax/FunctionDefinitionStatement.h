#pragma once

#include <Defines.h>
#include <Syntax/Statement.h>
#include <Syntax/Token.h>
#include <Syntax/Parameters.h>
#include <Syntax/Block.h>

class COMPILER_API FunctionDefinitionStatement : public Statement
{
public:
    FunctionDefinitionStatement(
        const Token& keyword, 
        const Token& name, 
        Parameters* parameters, 
        Block* body);

    [[nodiscard]] const Token& keyword() noexcept { return m_keyword; }
    [[nodiscard]] const Token& name() noexcept { return m_name; }
    [[nodiscard]] Parameters* parameters()  noexcept { return m_parameters; }
    [[nodiscard]] Block* body() noexcept { return m_body; }

private:
    Token m_keyword;
    Token m_name;
    Parameters* m_parameters;
    Block* m_body;
};
