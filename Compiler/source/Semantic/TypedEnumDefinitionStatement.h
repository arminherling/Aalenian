#pragma once

#include <Defines.h>
#include <Semantic/Type.h>
#include <Semantic/TypedStatement.h>
#include <Semantic/TypedEnumFieldDefinitionNode.h>
#include <QList>

class COMPILER_API TypedEnumDefinitionStatement : public TypedStatement
{
public:
    TypedEnumDefinitionStatement(
        QStringView name,
        Type type,
        Type baseType,
        const QList<TypedEnumFieldDefinitionNode*>& fields,
        Node* source);

    [[nodiscard]] QStringView name() const noexcept { return m_name; }
    [[nodiscard]] Type baseType() const noexcept { return m_baseType; }
    [[nodiscard]] QList<TypedEnumFieldDefinitionNode*> fields() const noexcept { return m_fields; }

private:
    QStringView m_name;
    Type m_baseType;
    QList<TypedEnumFieldDefinitionNode*> m_fields;
};
