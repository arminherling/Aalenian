#include "Number.h"

Number::Number(const Token& token)
    : Expression(NodeKind::Number)
    , m_token{ token }
{
}

Number::Number(
    const Token& token,
    const Token& colon,
    const Type& type)
    : Expression(NodeKind::Number)
    , m_token{ token }
    , m_colon{ colon }
    , m_type{ type }
{
}
