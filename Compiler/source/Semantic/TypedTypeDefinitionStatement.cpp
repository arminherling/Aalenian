#include "TypedTypeDefinitionStatement.h"

TypedTypeDefinitionStatement::TypedTypeDefinitionStatement(
    QStringView name,
    Type type,
    Node* source)
    : TypedStatement(source, NodeKind::TypedTypeDefinitionStatement, type)
    , m_name{ name }
{
}
