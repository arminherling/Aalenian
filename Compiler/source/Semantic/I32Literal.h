#pragma once

#include <Defines.h>
#include <Semantic/Type.h>
#include <Semantic/TypedExpression.h>

class COMPILER_API I32Literal : public TypedExpression
{
public:
    I32Literal(i32 value, Node* source, Type type);

    i32 value() { return m_value; }

private:
    i32 m_value;
};
