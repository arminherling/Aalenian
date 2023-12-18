#pragma once

#include <Syntax/Name.h>
#include <Syntax/Node.h>
#include <Syntax/Type.h>

class COMPILER_API Parameter : public Node
{
public:
    Parameter(
        Name* name, 
        const Token& colon, 
        const Type& type);

    [[nodiscard]] Name* name() const noexcept { return m_name; }
    [[nodiscard]] const Token& colon() noexcept { return m_colon; }
    [[nodiscard]] const Type& type() noexcept { return m_type; }

private:
    Name* m_name;
    Token m_colon;
    Type m_type;
};
