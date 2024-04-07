#pragma once

#include <Defines.h>
#include <Semantic/Type.h>
#include <Semantic/TypedExpression.h>

class COMPILER_API TypedFunctionCallExpression : public TypedExpression
{
public:
    TypedFunctionCallExpression(QStringView name, Node* source, Type type);

    [[nodiscard]] QStringView name() const noexcept { return m_name; }

private:
    QStringView m_name;
};
