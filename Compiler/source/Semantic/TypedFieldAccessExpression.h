#pragma once

#include <Defines.h>
#include <Semantic/Type.h>
#include <Semantic/TypedExpression.h>
#include <Semantic/Field.h>

class COMPILER_API TypedFieldAccessExpression : public TypedExpression
{
public:
    TypedFieldAccessExpression(Type scopeType, Field* field, Node* source);

    [[nodiscard]] Field* field() const noexcept { return m_field; }
    [[nodiscard]] QStringView fieldName() const noexcept { return m_field->name(); }
    [[nodiscard]] Type scopeType() const noexcept { return m_scopeType; }

private:
    Field* m_field;
    Type m_scopeType;
};
