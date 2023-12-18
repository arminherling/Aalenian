#include "FunctionCall.h"

FunctionCall::FunctionCall(
    const Token& nameToken, 
    ArgumentsNode* arguments)
    : Expression(NodeKind::FunctionCall)
    , m_nameToken{ nameToken }
    , m_arguments{ arguments }
{
}
