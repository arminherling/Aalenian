#pragma once

#include "CompilerApi.h"
#include "Node.h"

#include <QList>

class COMPILER_API ParseTree
{
public:
    ParseTree(const QList<Statement*>& statements);

    QList<Statement*> GlobalStatements();

private:
    QList<Statement*> m_statements;
};
