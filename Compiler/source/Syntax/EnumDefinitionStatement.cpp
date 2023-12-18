#include "EnumDefinitionStatement.h"

EnumDefinitionStatement::EnumDefinitionStatement(
    const Token& keyword,
    const Token& name,
    const std::optional<TypeNode>& baseType,
    BlockNode* body)
    : Statement(NodeKind::EnumDefinitionStatement)
    , m_keyword{ keyword }
    , m_name{ name }
    , m_baseType{ baseType }
    , m_body{ body }
{
}
