#include "ArgumentNode.h"

ArgumentNode::ArgumentNode(
    const std::optional<Token>& ref,
    Expression* expression)
    : Node(NodeKind::ArgumentNode)
    , m_ref{ ref }
    , m_expression{ expression }
{
}
