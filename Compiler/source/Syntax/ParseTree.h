#pragma once

#include <Compiler/API.h>
#include <Syntax/TokenBuffer.h>
#include <Syntax/Node.h>
#include <Syntax/Statement.h>

#include <QList>

class COMPILER_API ParseTree
{
public:
    ParseTree(
        const TokenBuffer& tokens, 
        const QList<Statement*>& statements);

    [[nodiscard]] QList<Statement*> globalStatements() const noexcept { return m_statements; };
    [[nodiscard]] const TokenBuffer& tokens() const noexcept { return m_tokens; }

private:
    TokenBuffer m_tokens;
    QList<Statement*> m_statements;
};
