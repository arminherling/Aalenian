#pragma once

#include <Defines.h>
#include <Semantic/Parameter.h>
#include <Semantic/Type.h>
#include <Semantic/TypedFieldDefinitionNode.h>
#include <Semantic/TypedStatement.h>
#include <QList>

class COMPILER_API TypedFunctionDefinitionStatement : public TypedStatement
{
public:
    TypedFunctionDefinitionStatement(
        QStringView name,
        Type type,
        const QList<Parameter*>& parameters,
        const QList<Type>& returnTypes,
        const QList<TypedStatement*>& statements,
        Node* source);

    [[nodiscard]] QStringView name() const noexcept { return m_name; }
    [[nodiscard]] const QList<Parameter*>& parameters() const noexcept { return m_parameters; }
    [[nodiscard]] const QList<Type>& returnTypes() const noexcept { return m_returnTypes; }
    [[nodiscard]] const QList<TypedStatement*>& body() const noexcept { return m_statements; }

private:
    QStringView m_name;
    QList<Parameter*> m_parameters;
    QList<Type> m_returnTypes;
    QList<TypedStatement*> m_statements;
};
