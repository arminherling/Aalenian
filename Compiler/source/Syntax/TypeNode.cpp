#include "TypeNode.h"

TypeNode::TypeNode(
    const std::optional<Token>& ref,
    NameExpression* name)
    : Node(NodeKind::TypeNode)
    , m_ref{ ref }
    , m_name{ name }
{
}
