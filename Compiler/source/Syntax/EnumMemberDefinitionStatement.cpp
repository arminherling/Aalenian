#include "EnumMemberDefinitionStatement.h"

EnumMemberDefinitionStatement::EnumMemberDefinitionStatement(NameExpression* name)
    : Statement(NodeKind::EnumMember)
    , m_name{ name }
{
}

EnumMemberDefinitionStatement::EnumMemberDefinitionStatement(
    NameExpression* name,
    const Token& equal,
    NumberLiteral* value)
    : Statement(NodeKind::EnumMember)
    , m_name{ name }
    , m_equal{ equal }
    , m_value{ value }
{
}
