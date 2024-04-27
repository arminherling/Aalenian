#include "TypeDatabase.h"

TypeDatabase::TypeDatabase()
    : m_invalidType{ Type::Undefined().id(), QString("???") }
    , m_nextId{ 100 }
{
    addBuiltinType(Type::Discard(), QString("_"));
    addBuiltinType(Type::Void(), QString("void"));
    addBuiltinTypesWithVariation(Type::Bool(), QString("bool"));
    addBuiltinTypesWithVariation(Type::U8(), QString("u8"));
    addBuiltinTypesWithVariation(Type::I32(), QString("i32"));
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
    auto type = createType(name, kind);

    if (scope != Type::Undefined())
    {
        auto& definition = getTypeDefinition(scope);
        definition.addFunction(type, name);
    }

    return type;
}

void TypeDatabase::addBuiltinTypesWithVariation(Type type, const QString& name) noexcept
{
    addBuiltinType(type, name);

    auto refTypeName = QString("ref %1").arg(name);
    auto refType = Type(type.id() + 1, type.kind());
    addBuiltinType(refType, refTypeName);

    //auto nullableTypeName = QString("%1?").arg(name);
    //auto nullableType = Type(type.id() + 2, type.kind());
    //addBuiltinType(nullableType, nullableTypeName);

    //auto nullableRefTypeName = QString("ref %1?").arg(name);
    //auto nullableRefType = Type(type.id() + 3, type.kind());
    //addBuiltinType(nullableRefType, nullableRefTypeName);
}

void TypeDatabase::addBuiltinType(Type type, const QString& name) noexcept
{
    m_typeNames.emplace(name, type);
    m_typeDefinitions.emplace(type.id(), TypeDefinition{ type.id(), name });
}
