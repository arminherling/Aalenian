#pragma once

#include <Defines.h>
#include <QList>
#include <Semantic/TypedStatement.h>
#include <Syntax/TokenBuffer.h>

class COMPILER_API TypedTree
{
public:
    TypedTree(
        const TokenBuffer& tokens,
        const QList<TypedStatement*>& statements);

    QList<TypedStatement*> GlobalStatements() const;
    const TokenBuffer& Tokens() { return m_tokens; }

private:
    TokenBuffer m_tokens;
    QList<TypedStatement*> m_statements;
};
