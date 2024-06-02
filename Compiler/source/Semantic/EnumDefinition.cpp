#include "EnumDefinition.h"

EnumDefinition::EnumDefinition(i32 id, const QString& name)
    : m_id{ id }
    , m_name{ name }
{
}

void EnumDefinition::addField(Type type, QStringView name, TypedExpression* expression) noexcept
{
    m_fields.emplace(name.toString(), new Field(type, name, expression));
}

Field* EnumDefinition::getFieldByName(QStringView fieldName) const noexcept
{
    auto name = fieldName.toString();
    if (m_fields.contains(name))
        return m_fields.at(name);
    else
        return nullptr;
}
