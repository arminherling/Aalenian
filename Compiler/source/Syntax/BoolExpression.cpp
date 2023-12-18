#include "BoolExpression.h"

BoolExpression::BoolExpression(bool value)
    : Expression(NodeKind::Bool)
    , m_value{ value }
{
}
