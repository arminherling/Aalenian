#pragma once

#include <Defines.h>
#include <Syntax/Node.h>
#include <Syntax/Name.h>

class COMPILER_API Type : public Node
{
public:
    Type(
        const std::optional<Token>& ref, 
        Name* name);

    [[nodiscard]] const std::optional<Token>& ref() const noexcept { return m_ref; }
    [[nodiscard]] bool isReference() const noexcept { return m_ref.has_value(); }
    [[nodiscard]] Name* name() const noexcept { return m_name; }

private:
    std::optional<Token> m_ref;
    Name* m_name;
};
