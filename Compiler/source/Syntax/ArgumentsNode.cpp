#include "ArgumentsNode.h"

ArgumentsNode::ArgumentsNode(
    const Token& openParenthesis,
    const QList<ArgumentNode*>& arguments,
    const Token& closeParenthesis)
    : Node(NodeKind::ArgumentsNode)
    , m_openParenthesis{ openParenthesis }
    , m_arguments{ arguments }
    , m_closeParenthesis{ closeParenthesis }
{
}
