#pragma once

#include <Defines.h>
#include <Syntax/Node.h>
#include <Semantic/TypedExpression.h>

class COMPILER_API TypedEnumFieldDefinitionNode : public Node
{
public:
    TypedEnumFieldDefinitionNode(QStringView name, TypedExpression* value);

    [[nodiscard]] QStringView name() const noexcept { return m_name; }
    [[nodiscard]] TypedExpression* value() const noexcept { return m_value; }
    [[nodiscard]] Type valueType() const noexcept { return m_value->type(); }

private:
    QStringView m_name;
    TypedExpression* m_value;
};
