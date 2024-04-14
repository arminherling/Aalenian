#pragma once

#include <Defines.h>
#include <Semantic/Type.h>
#include <Semantic/TypedStatement.h>
#include <Semantic/TypedFieldDefinitionNode.h>
#include <QList>

class COMPILER_API TypedFunctionDefinitionStatement : public TypedStatement
{
public:
    TypedFunctionDefinitionStatement(
        QStringView name,
        Type type,
        //const QList<Parameters*>& parameters,
        //const QList<Type>& returnTypes,
        //const QList<TypedStatement*>& statements,
        Node* source);

    [[nodiscard]] QStringView name() const noexcept { return m_name; }
    //[[nodiscard]] QList<Parameters*> parameters() const noexcept { return m_parameters; }
    //[[nodiscard]] QList<Type> returnTypes() const noexcept { return m_returnTypes; }
    //[[nodiscard]] QList<TypedStatement*>& body() const noexcept { return m_body; }

private:
    QStringView m_name;
    //QList<Parameters*> m_parameters;
    //QList<Type> m_returnTypes;
    //QList<TypedStatement*> m_statements;
};
