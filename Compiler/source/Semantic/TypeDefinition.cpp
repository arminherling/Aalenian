#include "TypeDefinition.h"

TypeDefinition::TypeDefinition(i32 id, const QString& name)
    : m_id{ id }
    , m_name{ name }
    , m_returnType{ Type::Undefined() }
{
}

void TypeDefinition::addField(Type type, QStringView name, TypedExpression* expression) noexcept
{
    m_fields.emplace(name.toString(), new Field(type, name, expression));
}

void TypeDefinition::addFunction(Type type, QStringView name) noexcept
{
    // TODO
}

void TypeDefinition::setParameters(const QList<Parameter*>& parameters)
{
    m_parameters = parameters;
}

void TypeDefinition::setReturnType(Type returnType)
{
    m_returnType = returnType;
}

Field* TypeDefinition::getFieldByName(QStringView fieldName) const noexcept
{
    auto name = fieldName.toString();
    if (m_fields.contains(name))
        return m_fields.at(name);
    else
        return nullptr;
}
