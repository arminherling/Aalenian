#include "BlockNode.h"

BlockNode::BlockNode(
    const Token& openBracket,
    const QList<Statement*>& statements,
    const Token& closeBracket)
    : Node(NodeKind::Block)
    , m_openBracket{ openBracket }
    , m_statements{ statements }
    , m_closeBracket{ closeBracket }
{
}
