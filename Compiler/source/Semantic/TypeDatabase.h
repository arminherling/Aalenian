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

    [[nodiscard]] Type getTypeByName(QStringView typeName) const noexcept;
    [[nodiscard]] TypeDefinition& getTypeDefinition(Type type) noexcept;

    [[nodiscard]] Type createType(QStringView name, TypeKind kind) noexcept;

private:
    std::unordered_map<QString, Type> m_typeNames;
    std::unordered_map<i32, TypeDefinition> m_typeDefinitions;
    TypeDefinition m_invalidType;
    i32 m_nextId;

    void addBuiltinType(Type type, QStringView name) noexcept;
};
