#include "TypedTypeDefinitionStatement.h"

TypedTypeDefinitionStatement::TypedTypeDefinitionStatement(
    QStringView name,
    Type type,
    const QList<TypedFieldDefinitionNode*>& fields,
    Node* source)
    : TypedStatement(source, NodeKind::TypedTypeDefinitionStatement, type)
    , m_name{ name }
    , m_fields{ fields }
{
}
