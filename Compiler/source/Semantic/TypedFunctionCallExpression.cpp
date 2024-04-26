#include "TypedFunctionCallExpression.h"

TypedFunctionCallExpression::TypedFunctionCallExpression(
    QStringView name, 
    Type functionType, 
    const QList<TypedExpression*>& arguments, 
    Node* source, 
    Type type)
    : TypedExpression(source, NodeKind::TypedFunctionCallExpression, type)
    , m_name{ name }
    , m_functionType{ functionType }
    , m_arguments{ arguments }
{
}
