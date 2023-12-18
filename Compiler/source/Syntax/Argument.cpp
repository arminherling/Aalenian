#include "Argument.h"

Argument::Argument(
    const std::optional<Token>& ref,
    Expression* expression)
    : Node(NodeKind::Argument)
    , m_ref{ ref }
    , m_expression{ expression }
{
}
