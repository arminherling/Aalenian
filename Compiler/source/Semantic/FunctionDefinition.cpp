#include "FunctionDefinition.h"

FunctionDefinition::FunctionDefinition(i32 id, const QString& name)
    : m_id{ id }
    , m_name{ name }
    , m_returnType{ Type::Undefined() }
{
}

void FunctionDefinition::setParameters(const QList<Parameter*>& parameters)
{
    m_parameters = parameters;
}

void FunctionDefinition::setReturnType(Type returnType)
{
    m_returnType = returnType;
}
