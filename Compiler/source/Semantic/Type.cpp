#include "Type.h"

Type::Type(i32 id)
    : m_id{ id }
{
}

bool operator==(Type lhs, Type rhs) noexcept
{
    return lhs.id() == rhs.id();
}

bool operator!=(Type lhs, Type rhs) noexcept
{
    return lhs.id() != rhs.id();
}
