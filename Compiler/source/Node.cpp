#include "Node.h"

Node::Node(NodeKind kind)
    : m_kind{ kind }
{
}

NodeKind Node::Kind()
{
    return m_kind;
}

Statement::Statement(NodeKind kind)
    : Node(kind)
{
}

Expression::Expression(NodeKind kind)
    : Node(kind)
{
}

Name::Name(const Token& token)
    : Expression(NodeKind::Name)
    , m_token{ token }
{
}

Number::Number(const Token& token)
    : Expression(NodeKind::Number)
    , m_token{ token }
{
}

AssignmentStatement::AssignmentStatement(Expression* leftExpression, const Token& equalsToken, Expression* rightExpression)
    : Statement(NodeKind::AssignmentStatement)
    , m_leftExpression{ leftExpression }
    , m_equalsToken{ equalsToken }
    , m_rightExpression{ rightExpression }
{
}
