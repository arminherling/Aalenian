#include "Parameters.h"

Parameters::Parameters(
    const Token& openParenthesis,
    const QList<ParameterNode*>& parameters,
    const Token& closeParenthesis)
    : Node(NodeKind::Parameters)
    , m_openParenthesis{ openParenthesis }
    , m_parameters{ parameters }
    , m_closeParenthesis{ closeParenthesis }
{
}
