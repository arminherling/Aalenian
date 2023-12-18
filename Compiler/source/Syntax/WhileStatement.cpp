#include "WhileStatement.h"

WhileStatement::WhileStatement(
    const Token& ifKeyword,
    Expression* condition,
    Block* body)
    : Statement(NodeKind::WhileStatement)
    , m_ifKeyword{ ifKeyword }
    , m_condition{ condition }
    , m_body{ body }
{
}
