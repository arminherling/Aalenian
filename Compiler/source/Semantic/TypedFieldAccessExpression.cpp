#include "TypedFieldAccessExpression.h"

TypedFieldAccessExpression::TypedFieldAccessExpression(Type scopeType, Field* field, Node* source)
    : TypedExpression(source, NodeKind::TypedFieldAccessExpression, field->type())
    , m_field{ field }
    , m_scopeType{ scopeType }
{
}
