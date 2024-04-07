#include "TypeDefinition.h"

TypeDefinition::TypeDefinition(i32 id, const QString& name, TypeKind kind)
    : m_id{ id }
    , m_name{ name }
    , m_kind{ kind }
{
}

void TypeDefinition::addField(Type type, QStringView name, TypedExpression* expression)
{
    m_fields.emplace(name.toString(), new Field(type, name, expression));
}

Field* TypeDefinition::getFieldByName(QStringView fieldName) const noexcept
{
    auto name = fieldName.toString();
    if (m_fields.contains(name))
        return m_fields.at(name);
    else
        return nullptr;
}
