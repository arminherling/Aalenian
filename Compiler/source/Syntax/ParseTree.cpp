#include <Syntax/ParseTree.h>

ParseTree::ParseTree(
    const TokenBuffer& tokens, 
    const QList<Statement*>& statements)
    : m_tokens{ tokens }
    , m_statements{ statements }
{
}

QList<Statement*> ParseTree::GlobalStatements() const
{
    return m_statements;
}
