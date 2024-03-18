#include "Environment.h"

void Environment::addBinding(QStringView identifier, Type type)
{
    m_bindings.try_emplace(identifier.toString(), type);
}

Type Environment::tryGetBinding(QStringView identifier)
{
    if (auto search = m_bindings.find(identifier.toString()); search != m_bindings.end())
        return search->second;
    else
        return Type::Undefined();
}
