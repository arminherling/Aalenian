#include "TypedGlobalValue.h"

TypedGlobalValue::TypedGlobalValue(QStringView name, Node* source, Type type)
    : TypedExpression(source, NodeKind::TypedGlobalValue, type)
    , m_name{ name }
{
}
