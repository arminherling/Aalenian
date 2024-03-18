#pragma once

#include <Defines.h>
#include <Semantic/Type.h>
#include <Semantic/TypedExpression.h>

class COMPILER_API TypedFunctionCallExpression : public TypedExpression
{
public:
    TypedFunctionCallExpression(QStringView name, Node* source, Type type);

    QStringView name() { return m_name; }

private:
    QStringView m_name;
};
