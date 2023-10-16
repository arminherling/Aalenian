#include "ParseTree.h"

ParseTree::ParseTree(const QList<Statement*>& statements)
    : m_statements{ statements }
{
}

QList<Statement*> ParseTree::GlobalStatements()
{
    return m_statements;
}
