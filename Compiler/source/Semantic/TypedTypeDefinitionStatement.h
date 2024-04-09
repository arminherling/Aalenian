#pragma once

#include <Defines.h>
#include <Semantic/Type.h>
#include <Semantic/TypedStatement.h>
#include <Semantic/TypedFieldDefinitionNode.h>
#include <QList>

class COMPILER_API TypedTypeDefinitionStatement : public TypedStatement
{
public:
    TypedTypeDefinitionStatement(
        QStringView name,
        Type type,
        const QList<TypedFieldDefinitionNode*>& fields,
        Node* source);

    [[nodiscard]] QStringView name() const noexcept { return m_name; }
    [[nodiscard]] QList<TypedFieldDefinitionNode*> fields() const noexcept { return m_fields; }

private:
    QStringView m_name;
    QList<TypedFieldDefinitionNode*> m_fields;
};
