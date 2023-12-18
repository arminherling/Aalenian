#include "EnumMember.h"

EnumMember::EnumMember(Name* name)
    : Statement(NodeKind::EnumMember)
    , m_name{ name }
{
}

EnumMember::EnumMember(
    Name* name,
    const Token& equal,
    Number* value)
    : Statement(NodeKind::EnumMember)
    , m_name{ name }
    , m_equal{ equal }
    , m_value{ value }
{
}
