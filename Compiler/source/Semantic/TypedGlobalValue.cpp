#include "TypedGlobalValue.h"

TypedGlobalValue::TypedGlobalValue(const QString& name, Node* source, Type type)
    : TypedExpression(source, NodeKind::TypedGlobalValue, type)
    , m_name{ name }
{
}
