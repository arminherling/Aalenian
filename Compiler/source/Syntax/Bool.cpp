#include "Bool.h"

Bool::Bool(bool value)
    : Expression(NodeKind::Bool)
    , m_value{ value }
{
}
