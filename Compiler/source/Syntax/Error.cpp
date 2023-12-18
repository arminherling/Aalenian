#include "Error.h"

Error::Error(const Token& token)
    : Expression(NodeKind::Error)
    , m_token{ token }
{
}
