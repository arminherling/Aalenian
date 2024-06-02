#pragma once

#include <Defines.h>
#include <Semantic/Field.h>
#include <Semantic/Type.h>
#include <Semantic/TypedExpression.h>
#include <QString>
#include <QHash>

class EnumDefinition
{
public:
    EnumDefinition(i32 id, const QString& name);

    [[nodiscard]] i32 id() const noexcept { return m_id; }
    [[nodiscard]] QString name() const noexcept { return m_name; }
    [[nodiscard]] Field* getFieldByName(QStringView fieldName) const noexcept;

    void addField(Type type, QStringView name, TypedExpression* expression) noexcept;

private:
    i32 m_id;
    QString m_name;
    std::unordered_map<QString, Field*> m_fields;
};
