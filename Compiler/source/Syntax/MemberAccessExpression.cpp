#include "MemberAccessExpression.h"

MemberAccessExpression::MemberAccessExpression(
    const Token& dot,
    Expression* expression)
    : Expression(NodeKind::MemberAccess)
    , m_dot{ dot }
    , m_expression{ expression }
{
}

