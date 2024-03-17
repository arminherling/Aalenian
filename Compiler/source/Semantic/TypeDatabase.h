#pragma once

#include <Defines.h>
#include <QHash>
#include <QStringView>
#include <Semantic/Type.h>
#include <Semantic/TypeDefinition.h>
#include <unordered_map>

class COMPILER_API TypeDatabase
{
public:
    TypeDatabase();

    Type getBuiltinNumberTypeByName(QStringView typeName);
    TypeDefinition getTypeDefinition(Type type);

private:
    std::unordered_map<QString, Type> m_builtinTypes;
    std::unordered_map<i32, TypeDefinition> m_typeDefinitions;
    TypeDefinition m_invalidType;

    void addBuiltinNumberType(i32 id, QStringView name);
};
