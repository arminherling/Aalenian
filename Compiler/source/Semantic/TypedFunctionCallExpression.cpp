#include "TypedFunctionCallExpression.h"

TypedFunctionCallExpression::TypedFunctionCallExpression(QStringView name, Type functionType, Node* source, Type type)
    : TypedExpression(source, NodeKind::TypedFunctionCallExpression, type)
    , m_name{ name }
    , m_functionType{ functionType }
{
}
