#pragma once

#include <Defines.h>
#include <Syntax/Node.h>
#include <Syntax/Token.h>
#include <Syntax/Statement.h>
#include <QList>

class COMPILER_API BlockNode : public Node
{
public:
    BlockNode(
        const Token& openBracket, 
        const QList<Statement*>& statements, 
        const Token& closeBracket);

    [[nodiscard]] const Token& openBracket() noexcept { return m_openBracket; }
    [[nodiscard]] const QList<Statement*>& statements() noexcept { return m_statements; }
    [[nodiscard]] const Token& closeBracket() noexcept { return m_closeBracket; }

private:
    Token m_openBracket;
    QList<Statement*> m_statements;
    Token m_closeBracket;
};
