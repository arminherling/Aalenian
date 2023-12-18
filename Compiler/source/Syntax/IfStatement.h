#pragma once

#include <Defines.h>
#include <Syntax/BlockNode.h>
#include <Syntax/Expression.h>
#include <Syntax/Statement.h>
#include <Syntax/Token.h>

class COMPILER_API IfStatement : public Statement
{
public:
    IfStatement(
        const Token& ifKeyword, 
        Expression* condition, 
        BlockNode* body);

    [[nodiscard]] Expression* condition() noexcept { return m_condition; }
    [[nodiscard]] BlockNode* body() noexcept { return m_body; }

private:
    Token m_ifKeyword;
    Expression* m_condition;
    BlockNode* m_body;
};
