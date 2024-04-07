#pragma once

#include <Defines.h>
#include <Semantic/Field.h>
#include <Semantic/Type.h>
#include <Semantic/TypedExpression.h>
#include <QList>
#include <QString>

enum class TypeKind
{
    Invalid,
    Builtin,
    Enum
};

class TypeDefinition
{
public:
    TypeDefinition(i32 id, const QString& name, TypeKind kind);

    [[nodiscard]] i32 id() const noexcept { return m_id; }
    [[nodiscard]] const QString& name() const noexcept { return m_name; }
    [[nodiscard]] TypeKind kind() const noexcept { return m_kind; }
    [[nodiscard]] Field* getFieldByName(QStringView fieldName) const noexcept;

    void addField(Type type, QStringView name, TypedExpression* expression);

private:
    i32 m_id;
    QString m_name;
    TypeKind m_kind;
    std::unordered_map<QString, Field*> m_fields;
};
