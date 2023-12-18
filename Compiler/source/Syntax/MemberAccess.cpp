#include "MemberAccess.h"

MemberAccess::MemberAccess(
    const Token& dot,
    Expression* expression)
    : Expression(NodeKind::MemberAccess)
    , m_dot{ dot }
    , m_expression{ expression }
{
}

