#include "NameExpression.h"

NameExpression::NameExpression(const Token& token)
    : Expression(NodeKind::Name)
    , m_token{ token }
{
}
