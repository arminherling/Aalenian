#include "TypedEnumDefinitionStatement.h"

TypedEnumDefinitionStatement::TypedEnumDefinitionStatement(
    QStringView name,
    Type type,
    Type baseType,
    const QList<TypedEnumFieldDefinitionNode*>& fields,
    Node* source)
    : TypedStatement(source, NodeKind::TypedEnumDefinitionStatement, type)
    , m_name{ name }
    , m_baseType{ baseType }
    , m_fields{ fields }
{
}
