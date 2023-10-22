#pragma once

#include "CompilerApi.h"
#include "TokenBuffer.h"
#include "Node.h"

#include <QList>

class COMPILER_API ParseTree
{
public:
    ParseTree(const TokenBuffer& tokens, const QList<Statement*>& statements);

    QList<Statement*> GlobalStatements() const;
    const TokenBuffer& Tokens() { return m_tokens; }

private:
    TokenBuffer m_tokens;
    QList<Statement*> m_statements;
};
