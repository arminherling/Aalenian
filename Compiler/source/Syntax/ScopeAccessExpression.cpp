#include "ScopeAccessExpression.h"

ScopeAccessExpression::ScopeAccessExpression(
    const Token& doubleColon,
    Expression* expression)
    : Expression(NodeKind::ScopeAccess)
    , m_doubleColon{ doubleColon }
    , m_expression{ expression }
{
}
