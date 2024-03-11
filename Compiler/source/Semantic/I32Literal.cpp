#include "I32Literal.h"

I32Literal::I32Literal(i32 value, Node* source, Type type)
    : TypedExpression(source, NodeKind::I32Literal, type)
    , m_value{ value }
{
}
