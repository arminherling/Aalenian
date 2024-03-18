#include "TypeDatabase.h"

TypeDatabase::TypeDatabase()
    : m_invalidType{ Type::Invalid().id(), QString("???") }
{
    addBuiltinNumberType(Type::I32().id(), QStringView(u"i32"));
}

Type TypeDatabase::getBuiltinNumberTypeByName(QStringView typeName) const noexcept
{
    auto name = typeName.toString();
    if (m_builtinTypes.contains(name))
        return m_builtinTypes.at(name);
    else
        return Type::Invalid();
}

TypeDefinition& TypeDatabase::getTypeDefinition(Type type) noexcept
{
    auto id = type.id();
    if (m_typeDefinitions.contains(id))
        return m_typeDefinitions.at(id);
    else
        return m_invalidType;
}

void TypeDatabase::addBuiltinNumberType(i32 id, QStringView name)
{
    auto typeName = name.toString();
    m_builtinTypes.emplace(typeName, Type{ id });
    m_typeDefinitions.emplace(id, TypeDefinition{ id, typeName });
}
