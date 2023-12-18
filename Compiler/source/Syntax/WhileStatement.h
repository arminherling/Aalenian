#pragma once

#include <Defines.h>
#include <Syntax/Block.h>
#include <Syntax/Expression.h>
#include <Syntax/Statement.h>
#include <Syntax/Token.h>

class COMPILER_API WhileStatement : public Statement
{
public:
    WhileStatement(
        const Token& ifKeyword, 
        Expression* condition, 
        Block* body);

    [[nodiscard]] Expression* condition() noexcept { return m_condition; }
    [[nodiscard]] Block* body() noexcept { return m_body; }

private:
    Token m_ifKeyword;
    Expression* m_condition;
    Block* m_body;
};
