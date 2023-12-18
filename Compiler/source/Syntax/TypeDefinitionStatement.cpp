#include "TypeDefinitionStatement.h"

TypeDefinitionStatement::TypeDefinitionStatement(
    const Token& keyword,
    const Token& name,
    Block* body)
    : Statement(NodeKind::TypeDefinitionStatement)
    , m_keyword{ keyword }
    , m_name{ name }
    , m_body{ body }
{
}
