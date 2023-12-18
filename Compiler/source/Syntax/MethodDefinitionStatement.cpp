#include "MethodDefinitionStatement.h"

MethodDefinitionStatement::MethodDefinitionStatement(
    const Token& keyword,
    const Token& name,
    Parameters* parameters,
    Block* body)
    : Statement(NodeKind::MethodDefinitionStatement)
    , m_keyword{ keyword }
    , m_name{ name }
    , m_parameters{ parameters }
    , m_body{ body }
{
}
