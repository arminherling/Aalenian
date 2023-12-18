#include "BoolLiteral.h"

BoolLiteral::BoolLiteral(bool value)
    : Expression(NodeKind::BoolLiteral)
    , m_value{ value }
{
}
