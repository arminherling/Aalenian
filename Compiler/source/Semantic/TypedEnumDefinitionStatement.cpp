#include "TypedEnumDefinitionStatement.h"

TypedEnumDefinitionStatement::TypedEnumDefinitionStatement(
    QStringView name,
    Type type,
    Type baseType,
    Node* source)
    : TypedStatement(source, NodeKind::TypedEnumDefinitionStatement, type)
    , m_name{ name }
    , m_baseType{ baseType }
{
}
