#include "Arguments.h"

Arguments::Arguments(
    const Token& openParenthesis,
    const QList<Argument*>& arguments,
    const Token& closeParenthesis)
    : Node(NodeKind::Arguments)
    , m_openParenthesis{ openParenthesis }
    , m_arguments{ arguments }
    , m_closeParenthesis{ closeParenthesis }
{
}
