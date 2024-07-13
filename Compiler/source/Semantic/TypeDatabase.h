#pragma once

#include <Defines.h>
#include <Compiler/API.h>
#include <Semantic/EnumDefinition.h>
#include <Semantic/Type.h>
#include <Semantic/TypeDefinition.h>
#include <Semantic/FunctionDefinition.h>

#include <QHash>
#include <QStringView>

#include <unordered_map>

class COMPILER_API TypeDatabase
{
public:
    TypeDatabase();

    [[nodiscard]] Type getTypeByName(QStringView typeName) const noexcept;
    [[nodiscard]] EnumDefinition& getEnumDefinition(Type type) noexcept;
    [[nodiscard]] TypeDefinition& getTypeDefinition(Type type) noexcept;
    [[nodiscard]] FunctionDefinition& getFunctionDefinition(Type type) noexcept;

    [[nodiscard]] Type createEnum(QStringView name) noexcept;
    [[nodiscard]] Type createType(QStringView name, TypeKind kind) noexcept;
    [[nodiscard]] Type createFunction(QStringView name) noexcept;

private:
    std::unordered_map<QString, Type> m_names;
    std::unordered_map<i32, EnumDefinition> m_enumDefinitions;
    std::unordered_map<i32, TypeDefinition> m_typeDefinitions;
    std::unordered_map<i32, FunctionDefinition> m_functionDefinitions;
    i32 m_nextId;

    void addBuiltinTypesWithVariation(Type type, const QString& name) noexcept;
    void addBuiltinType(Type type, const QString& name) noexcept;
};
