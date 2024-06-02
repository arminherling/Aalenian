#pragma once

#include <Defines.h>
#include <Semantic/Parameter.h>
#include <Semantic/Type.h>
#include <Semantic/TypedExpression.h>
#include <QHash>
#include <QString>

class FunctionDefinition
{
public:
    FunctionDefinition(i32 id, const QString& name);

    [[nodiscard]] i32 id() const noexcept { return m_id; }
    [[nodiscard]] QString name() const noexcept { return m_name; }
    [[nodiscard]] QList<Parameter*> parameters() const noexcept { return m_parameters; }
    [[nodiscard]] Type returnType() const noexcept { return m_returnType; }

    void setParameters(const QList<Parameter*>& parameters);
    void setReturnType(Type returnType);

private:
    i32 m_id;
    QString m_name;
    QList<Parameter*> m_parameters;
    Type m_returnType;
};
