#include "FunctionDefinitionStatement.h"

FunctionDefinitionStatement::FunctionDefinitionStatement(
    const Token& keyword,
    const Token& name,
    Parameters* parameters,
    Block* body)
    : Statement(NodeKind::FunctionDefinitionStatement)
    , m_keyword{ keyword }
    , m_name{ name }
    , m_parameters{ parameters }
    , m_body{ body }
{
}
