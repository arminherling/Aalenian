#include "TypeDatabase.h"

TypeDatabase::TypeDatabase()
    : m_nextId{ 100 }
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
    if (m_names.contains(name))
        return m_names.at(name);
    else
        return Type::Undefined();
}

EnumDefinition& TypeDatabase::getEnumDefinition(Type type) noexcept
{
    static auto invalidEnum = EnumDefinition{ Type::Undefined().id(), QString("???") };

    auto id = type.id();
    if (m_enumDefinitions.contains(id))
        return m_enumDefinitions.at(id);
    else
        return invalidEnum;
}

TypeDefinition& TypeDatabase::getTypeDefinition(Type type) noexcept
{
    static auto invalidType = TypeDefinition{ Type::Undefined().id(), QString("???") };

    auto id = type.id();
    if (m_typeDefinitions.contains(id))
        return m_typeDefinitions.at(id);
    else
        return invalidType;
}

FunctionDefinition& TypeDatabase::getFunctionDefinition(Type type) noexcept
{
    static auto invalidFunction = FunctionDefinition{ Type::Undefined(), QString("???") };

    auto id = type.id();
    if (m_functionDefinitions.contains(id))
        return m_functionDefinitions.at(id);
    else
        return invalidFunction;
}

Type TypeDatabase::createEnum(QStringView name) noexcept
{
    auto enumName = name.toString();
    m_names.emplace(enumName, Type{ m_nextId, TypeKind::Enum });
    m_enumDefinitions.emplace(m_nextId, EnumDefinition{ m_nextId, enumName });
    return Type{ m_nextId++, TypeKind::Enum };
}

Type TypeDatabase::createType(QStringView name, TypeKind kind) noexcept
{
    auto typeName = name.toString();
    m_names.emplace(typeName, Type{ m_nextId, kind });
    m_typeDefinitions.emplace(m_nextId, TypeDefinition{ m_nextId, typeName });
    return Type{ m_nextId++, kind };
}

Type TypeDatabase::createFunction(QStringView name) noexcept
{
    auto functionName = name.toString();
    auto functionType = Type{ m_nextId++, TypeKind::Function };
    m_names.emplace(functionName, functionType);
    m_functionDefinitions.emplace(m_nextId, FunctionDefinition{ functionType, functionName });
    return functionType;
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
    m_names.emplace(name, type);
    m_typeDefinitions.emplace(type.id(), TypeDefinition{ type.id(), name });
}
