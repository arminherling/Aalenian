#include "TypeDatabase.h"

TypeDatabase::TypeDatabase()
    : m_invalidType{ Type::Invalid().id(), QString("???") }
{
    addBuiltinNumberType(Type::I32().id(), QStringView(u"i32"));
}

Type TypeDatabase::getBuiltinNumberTypeByName(QStringView typeName)
{
    if (auto search = m_builtinTypes.find(typeName.toString()); search != m_builtinTypes.end())
        return search->second;
    else
        return Type::Invalid();
}

TypeDefinition TypeDatabase::getTypeDefinition(Type type)
{
    if (auto search = m_typeDefinitions.find(type.id()); search != m_typeDefinitions.end())
        return search->second;
    else
        return m_invalidType;
}

void TypeDatabase::addBuiltinNumberType(i32 id, QStringView name)
{
    auto typeName = name.toString();
    m_builtinTypes.emplace(typeName, Type{ id });
    m_typeDefinitions.emplace(id, TypeDefinition{ id, typeName });
}
