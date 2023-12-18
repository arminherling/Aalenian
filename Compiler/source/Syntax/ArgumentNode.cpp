#include "ArgumentNode.h"

ArgumentNode::ArgumentNode(
    const std::optional<Token>& ref,
    Expression* expression)
    : Node(NodeKind::Argument)
    , m_ref{ ref }
    , m_expression{ expression }
{
}
