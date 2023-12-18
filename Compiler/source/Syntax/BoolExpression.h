#pragma once

#include <Defines.h>
#include <Syntax/Expression.h>

class COMPILER_API BoolExpression : public Expression
{
public:
    BoolExpression(bool value);

    [[nodiscard]] bool value() noexcept { return m_value; }

private:
    bool m_value;
};
