#pragma once

#include <Defines.h>
#include <Semantic/Type.h>
#include <Semantic/TypedExpression.h>

class COMPILER_API TypedGlobalValue : public TypedExpression
{
public:
    TypedGlobalValue(QStringView name, Node* source, Type type);

    QStringView name() const noexcept { return m_name; }

private:
    QStringView m_name;
};
