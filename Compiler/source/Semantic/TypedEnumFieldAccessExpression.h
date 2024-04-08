#pragma once

#include <Defines.h>
#include <Semantic/Type.h>
#include <Semantic/TypedExpression.h>
#include <Semantic/Field.h>

class COMPILER_API TypedEnumFieldAccessExpression : public TypedExpression
{
public:
    TypedEnumFieldAccessExpression(Type type, Field* field, Node* source);

    [[nodiscard]] Field* field() const noexcept { return m_field; }
    [[nodiscard]] QStringView fieldName() const noexcept { return m_field->name(); }

private:
    Field* m_field;
};