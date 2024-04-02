#pragma once

#include <Defines.h>
#include <Semantic/Type.h>
#include <Semantic/TypedExpression.h>

class COMPILER_API U8Literal : public TypedExpression
{
public:
    U8Literal(u8 value, Node* source, Type type);

    u8 value() { return m_value; }

private:
    u8 m_value;
};
