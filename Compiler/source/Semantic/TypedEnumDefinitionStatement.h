#pragma once

#include <Defines.h>
#include <Semantic/Type.h>
#include <Semantic/TypedStatement.h>

class COMPILER_API TypedEnumDefinitionStatement : public TypedStatement
{
public:
    TypedEnumDefinitionStatement(
        QStringView name,
        Type type,
        Type baseType,
        // TODO fields
        Node* source);

    [[nodiscard]] QStringView name() const noexcept { return m_name; }
    [[nodiscard]] Type baseType() const noexcept { return m_baseType; }

private:
    QStringView m_name;
    Type m_baseType;
};
