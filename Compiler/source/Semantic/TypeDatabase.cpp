#include "TypeDatabase.h"

TypeDatabase::TypeDatabase()
    : m_invalidType{ Type::Undefined().id(), QString("???"), TypeKind::Invalid }
    , m_nextId{ 100 }
{
    addBuiltinType(Type::Discard(), QStringView(u"_"));
    addBuiltinType(Type::U8(), QStringView(u"u8"));
    addBuiltinType(Type::I32(), QStringView(u"i32"));
}

Type TypeDatabase::getTypeByName(QStringView typeName) const noexcept
{
    auto name = typeName.toString();
    if (m_typeNames.contains(name))
        return m_typeNames.at(name);
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

Type TypeDatabase::createType(QStringView name, TypeKind kind)
{
    auto typeName = name.toString();
    m_typeNames.emplace(typeName, Type{ m_nextId });
    m_typeDefinitions.emplace(m_nextId, TypeDefinition{ m_nextId, typeName, kind });
    return Type{ m_nextId++ };
}

void TypeDatabase::addBuiltinType(Type type, QStringView name)
{
    auto id = type.id();
    auto typeName = name.toString();
    m_typeNames.emplace(typeName, Type{ id });
    m_typeDefinitions.emplace(id, TypeDefinition{ id, typeName, TypeKind::Builtin });
}
