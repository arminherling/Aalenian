#include "ParameterNode.h"

ParameterNode::ParameterNode(
    NameExpression* name,
    const Token& colon,
    const TypeName& type)
    : Node(NodeKind::ParameterNode)
    , m_name{ name }
    , m_colon{ colon }
    , m_type{ type }
{
}
