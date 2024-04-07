#include "TypedEnumFieldAccessExpression.h"

TypedEnumFieldAccessExpression::TypedEnumFieldAccessExpression(Type type, Field* field, Node* source)
    : TypedExpression(source, NodeKind::TypedEnumFieldAccessExpression, type)
    , m_field{ field }
{
}
