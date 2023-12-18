#include "ScopeAccess.h"

ScopeAccess::ScopeAccess(
    const Token& doubleColon,
    Expression* expression)
    : Expression(NodeKind::ScopeAccess)
    , m_doubleColon{ doubleColon }
    , m_expression{ expression }
{
}
