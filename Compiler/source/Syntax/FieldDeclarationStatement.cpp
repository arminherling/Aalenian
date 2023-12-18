#include "FieldDeclarationStatement.h"

FieldDeclarationStatement::FieldDeclarationStatement(
    Name* name,
    const std::optional<Token>& colon,
    const std::optional<Type>& type,
    const std::optional<Token>& equals,
    const std::optional<Expression*>& expression)
    : Statement(NodeKind::FieldDeclarationStatement)
    , m_name{ name }
    , m_colon{ colon }
    , m_type{ type }
    , m_equals{ equals }
    , m_expression{ expression }
{
}
