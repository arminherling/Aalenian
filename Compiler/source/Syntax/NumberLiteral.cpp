#include "NumberLiteral.h"

NumberLiteral::NumberLiteral(const Token& token)
    : Expression(NodeKind::Number)
    , m_token{ token }
{
}

NumberLiteral::NumberLiteral(
    const Token& token,
    const Token& colon,
    const TypeNode& type)
    : Expression(NodeKind::Number)
    , m_token{ token }
    , m_colon{ colon }
    , m_type{ type }
{
}
