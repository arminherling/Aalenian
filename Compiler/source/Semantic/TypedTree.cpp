#include "TypedTree.h"

TypedTree::TypedTree(
    const TokenBuffer& tokens,
    const QList<TypedStatement*>& statements)
    : m_tokens{ tokens }
    , m_statements{ statements }
{
}

QList<TypedStatement*> TypedTree::GlobalStatements() const
{
    return m_statements;
}
