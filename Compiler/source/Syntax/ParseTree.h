#pragma once

#include <Defines.h>
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

    QList<Statement*> GlobalStatements() const;
    const TokenBuffer& Tokens() { return m_tokens; }

private:
    TokenBuffer m_tokens;
    QList<Statement*> m_statements;
};
