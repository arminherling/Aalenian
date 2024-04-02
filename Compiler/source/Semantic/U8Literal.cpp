#include "U8Literal.h"

U8Literal::U8Literal(u8 value, Node* source, Type type)
    : TypedExpression(source, NodeKind::U8Literal, type)
    , m_value{ value }
{
}
