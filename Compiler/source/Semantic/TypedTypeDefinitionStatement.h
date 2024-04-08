#pragma once

#include <Defines.h>
#include <Semantic/Type.h>
#include <Semantic/TypedStatement.h>
#include <QList>

class COMPILER_API TypedTypeDefinitionStatement : public TypedStatement
{
public:
    TypedTypeDefinitionStatement(
        QStringView name,
        Type type,
        Node* source);

    [[nodiscard]] QStringView name() const noexcept { return m_name; }

private:
    QStringView m_name;
};
