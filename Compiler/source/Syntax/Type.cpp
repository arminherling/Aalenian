#include "Type.h"

Type::Type(
    const std::optional<Token>& ref,
    Name* name)
    : Node(NodeKind::Type)
    , m_ref{ ref }
    , m_name{ name }
{
}
