#include "TypedFunctionCallExpression.h"

TypedFunctionCallExpression::TypedFunctionCallExpression(QStringView name, Node* source, Type type)
    : TypedExpression(source, NodeKind::TypedFunctionCallExpression, type)
    , m_name{ name }
{
}
