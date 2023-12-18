#pragma once

#include <Syntax/NameExpression.h>
#include <Syntax/Node.h>
#include <Syntax/Type.h>

class COMPILER_API ParameterNode : public Node
{
public:
    ParameterNode(
        NameExpression* name,
        const Token& colon, 
        const Type& type);

    [[nodiscard]] NameExpression* name() const noexcept { return m_name; }
    [[nodiscard]] const Token& colon() noexcept { return m_colon; }
    [[nodiscard]] const Type& type() noexcept { return m_type; }

private:
    NameExpression* m_name;
    Token m_colon;
    Type m_type;
};
