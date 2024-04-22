#pragma once

#include <Defines.h>
#include <Semantic/Field.h>
#include <Semantic/Type.h>
#include <Semantic/TypedExpression.h>
#include <QList>
#include <QString>

class TypeDefinition
{
public:
    TypeDefinition(i32 id, const QString& name);

    [[nodiscard]] i32 id() const noexcept { return m_id; }
    [[nodiscard]] const QString& name() const noexcept { return m_name; }
    [[nodiscard]] QList<Type> returnTypes() const noexcept { return m_returnTypes; }
    [[nodiscard]] Field* getFieldByName(QStringView fieldName) const noexcept;

    void addField(Type type, QStringView name, TypedExpression* expression) noexcept;
    void addFunction(Type type, QStringView name) noexcept;
    void setReturnTypes(const QList<Type>& returnTypes);

private:
    i32 m_id;
    QString m_name;
    std::unordered_map<QString, Field*> m_fields;
    QList<Type> m_returnTypes;
};
