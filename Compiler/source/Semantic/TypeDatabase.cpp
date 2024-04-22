#include "TypeDatabase.h"

TypeDatabase::TypeDatabase()
    : m_invalidType{ Type::Undefined().id(), QString("???") }
    , m_nextId{ 100 }
{
    addBuiltinType(Type::Discard(), QStringView(u"_"));
    addBuiltinType(Type::Void(), QStringView(u"void"));
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

Type TypeDatabase::createType(QStringView name, TypeKind kind) noexcept
{
    auto typeName = name.toString();
    m_typeNames.emplace(typeName, Type{ m_nextId, kind });
    m_typeDefinitions.emplace(m_nextId, TypeDefinition{ m_nextId, typeName });
    return Type{ m_nextId++, kind };
}

Type TypeDatabase::createFunction(Type scope, QStringView name, TypeKind kind) noexcept
{
    auto type = Type{ m_nextId++, kind };
    
    if (scope != Type::Undefined())
    {
        auto& definition = getTypeDefinition(scope);
        definition.addFunction(type, name);
    }

    return type;
}

void TypeDatabase::addBuiltinType(Type type, QStringView name) noexcept
{
    auto id = type.id();
    auto typeName = name.toString();
    m_typeNames.emplace(typeName, type);
    m_typeDefinitions.emplace(id, TypeDefinition{ id, typeName });
}
