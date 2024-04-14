#include "TypedFunctionDefinitionStatement.h"

TypedFunctionDefinitionStatement::TypedFunctionDefinitionStatement(
    QStringView name,
    Type type,
    //const QList<Parameters*>& parameters,
    //const QList<Type>& returnTypes,
    //const QList<TypedStatement*>& statements,
    Node* source)
    : TypedStatement(source, NodeKind::TypedFunctionDefinitionStatement, type)
    , m_name{ name }
    //, m_parameters{ parameters }
    //, m_returnTypes{ returnTypes }
    //, m_statements{ statements }
{
}