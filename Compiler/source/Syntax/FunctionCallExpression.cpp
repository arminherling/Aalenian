#include "FunctionCallExpression.h"

FunctionCallExpression::FunctionCallExpression(
    const Token& nameToken, 
    ArgumentsNode* arguments)
    : Expression(NodeKind::FunctionCall)
    , m_nameToken{ nameToken }
    , m_arguments{ arguments }
{
}
