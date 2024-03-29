#include "TypeDatabase.h"

TypeDatabase::TypeDatabase()
    : m_invalidType{ Type::Undefined().id(), QString("???") }
{
    addBuiltinType(Type::Discard(), QStringView(u"_"));
    addBuiltinType(Type::I32(), QStringView(u"i32"));
}

Type TypeDatabase::getBuiltinTypeByName(QStringView typeName) const noexcept
{
    auto name = typeName.toString();
    if (m_builtinTypes.contains(name))
        return m_builtinTypes.at(name);
    else
        return Type::Undefined();
}

TypeDefinition& TypeDatabase::getTypeDefinition(Type type) noexcept
{
    auto id = type.id();
    if (m_typeDefinitions.contains(id))
        return m_typeDefinitions.at(id);
    else
        return m_invalidType;
}

void TypeDatabase::addBuiltinType(Type type, QStringView name)
{
    auto id = type.id();
    auto typeName = name.toString();
    m_builtinTypes.emplace(typeName, Type{ id });
    m_typeDefinitions.emplace(id, TypeDefinition{ id, typeName });
}
