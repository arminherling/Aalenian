#pragma once

#include <Defines.h>
#include <QHash>
#include <QStringView>
#include <Semantic/EnumDefinition.h>
#include <Semantic/Type.h>
#include <Semantic/TypeDefinition.h>
#include <unordered_map>

class COMPILER_API TypeDatabase
{
public:
    TypeDatabase();

    [[nodiscard]] Type getTypeByName(QStringView typeName) const noexcept;
    [[nodiscard]] EnumDefinition& getEnumDefinition(Type type) noexcept;
    [[nodiscard]] TypeDefinition& getTypeDefinition(Type type) noexcept;

    [[nodiscard]] Type createEnum(QStringView name) noexcept;
    [[nodiscard]] Type createType(QStringView name, TypeKind kind) noexcept;
    [[nodiscard]] Type createFunction(Type scope, QStringView name, TypeKind kind) noexcept;

private:
    std::unordered_map<QString, Type> m_names;
    std::unordered_map<i32, EnumDefinition> m_enumDefinitions;
    std::unordered_map<i32, TypeDefinition> m_typeDefinitions;
    EnumDefinition m_invalidEnum;
    TypeDefinition m_invalidType;
    i32 m_nextId;

    void addBuiltinTypesWithVariation(Type type, const QString& name) noexcept;
    void addBuiltinType(Type type, const QString& name) noexcept;
};
