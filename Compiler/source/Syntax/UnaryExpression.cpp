#include "UnaryExpression.h"

UnaryExpression::UnaryExpression(
    const Token& unaryOperator, 
    Expression* expression)
    : Expression(NodeKind::UnaryExpression)
    , m_unaryOperator{ unaryOperator }
    , m_expression{ expression }
{
}
