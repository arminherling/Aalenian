#pragma once

#include <Defines.h>
#include <Syntax/Expression.h>

class COMPILER_API Bool : public Expression
{
public:
    Bool(bool value);

    [[nodiscard]] bool value() noexcept { return m_value; }

private:
    bool m_value;
};
