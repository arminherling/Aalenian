#include "ParameterNode.h"

ParameterNode::ParameterNode(
    NameExpression* name,
    const Token& colon,
    const TypeNode& type)
    : Node(NodeKind::Parameter)
    , m_name{ name }
    , m_colon{ colon }
    , m_type{ type }
{
}
