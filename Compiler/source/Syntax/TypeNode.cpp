#include "TypeNode.h"

TypeNode::TypeNode(
    const std::optional<Token>& ref,
    NameExpression* name)
    : Node(NodeKind::Type)
    , m_ref{ ref }
    , m_name{ name }
{
}
