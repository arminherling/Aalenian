#include "Parameter.h"

Parameter::Parameter(
    Name* name,
    const Token& colon,
    const Type& type)
    : Node(NodeKind::Parameter)
    , m_name{ name }
    , m_colon{ colon }
    , m_type{ type }
{
}
