#include "TypedEnumFieldDefinitionNode.h"

TypedEnumFieldDefinitionNode::TypedEnumFieldDefinitionNode(QStringView name, TypedExpression* value)
    : Node(NodeKind::TypedEnumFieldDefinitionNode)
    , m_name{ name }
    , m_value{ value }
{
}
