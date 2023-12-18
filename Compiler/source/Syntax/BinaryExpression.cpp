#include "BinaryExpression.h"

BinaryExpression::BinaryExpression(
    Expression* leftExpression, 
    const Token& binaryOperator, 
    Expression* rightExpression)
    : Expression(NodeKind::BinaryExpression)
    , m_leftExpression{ leftExpression }
    , m_binaryOperator{ binaryOperator }
    , m_rightExpression{ rightExpression }
{
}
