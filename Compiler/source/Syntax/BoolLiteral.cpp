#include "BoolLiteral.h"

BoolLiteral::BoolLiteral(bool value)
    : Expression(NodeKind::Bool)
    , m_value{ value }
{
}
