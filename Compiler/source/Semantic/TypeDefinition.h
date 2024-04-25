#pragma once

#include <Defines.h>
#include <Semantic/Field.h>
#include <Semantic/Parameter.h>
#include <Semantic/Type.h>
#include <Semantic/TypedExpression.h>
#include <QList>
#include <QString>

class TypeDefinition
{
public:
    TypeDefinition(i32 id, const QString& name);

    [[nodiscard]] i32 id() const noexcept { return m_id; }
    [[nodiscard]] QString name() const noexcept { return m_name; }
    [[nodiscard]] QList<Parameter*> parameters() const noexcept { return m_parameters; }
    [[nodiscard]] Type returnType() const noexcept { return m_returnType; }
    [[nodiscard]] Field* getFieldByName(QStringView fieldName) const noexcept;

    void addField(Type type, QStringView name, TypedExpression* expression) noexcept;
    void addFunction(Type type, QStringView name) noexcept;
    void setParameters(const QList<Parameter*>& parameters);
    void setReturnType(Type returnType);

private:
    i32 m_id;
    QString m_name;
    std::unordered_map<QString, Field*> m_fields;
    QList<Parameter*> m_parameters;
    Type m_returnType;
};
