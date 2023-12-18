#include "Name.h"

Name::Name(const Token& token)
    : Expression(NodeKind::Name)
    , m_token{ token }
{
}
