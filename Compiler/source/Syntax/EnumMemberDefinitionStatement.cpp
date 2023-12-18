#include "EnumMemberDefinitionStatement.h"

EnumMemberDefinitionStatement::EnumMemberDefinitionStatement(Name* name)
    : Statement(NodeKind::EnumMember)
    , m_name{ name }
{
}

EnumMemberDefinitionStatement::EnumMemberDefinitionStatement(
    Name* name,
    const Token& equal,
    Number* value)
    : Statement(NodeKind::EnumMember)
    , m_name{ name }
    , m_equal{ equal }
    , m_value{ value }
{
}
