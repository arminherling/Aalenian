#include "IfStatement.h"

IfStatement::IfStatement(
    const Token& ifKeyword,
    Expression* condition,
    Block* body)
    : Statement(NodeKind::IfStatement)
    , m_ifKeyword{ ifKeyword }
    , m_condition{ condition }
    , m_body{ body }
{
}
