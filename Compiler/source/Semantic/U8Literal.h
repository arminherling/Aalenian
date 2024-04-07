#pragma once

#include <Defines.h>
#include <Semantic/Type.h>
#include <Semantic/TypedExpression.h>

class COMPILER_API U8Literal : public TypedExpression
{
public:
    U8Literal(u8 value, Node* source, Type type);

    [[nodiscard]] u8 value() const noexcept { return m_value; }

private:
    u8 m_value;
};
