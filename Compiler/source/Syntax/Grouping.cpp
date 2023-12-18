#include "Grouping.h"

Grouping::Grouping(
    const Token& openParenthesis,
    Expression* expression,
    const Token& closeParenthesis)
    : Expression(NodeKind::Grouping)
    , m_openParenthesis{ openParenthesis }
    , m_expression{ expression }
    , m_closeParenthesis{ closeParenthesis }
{
}
