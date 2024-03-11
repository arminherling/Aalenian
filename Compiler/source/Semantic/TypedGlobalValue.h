#pragma once

#include <Defines.h>
#include <Semantic/Type.h>
#include <Semantic/TypedExpression.h>

class COMPILER_API TypedGlobalValue : public TypedExpression
{
public:
    TypedGlobalValue(const QString& name, Node* source, Type type);

    QString& name() { return m_name; }

private:
    QString m_name;
};
