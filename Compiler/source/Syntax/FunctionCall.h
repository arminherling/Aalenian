#pragma once

#include <Defines.h>
#include <Syntax/Expression.h>
#include <Syntax/Token.h>
#include <Syntax/Arguments.h>

class COMPILER_API FunctionCall : public Expression
{
public:
    FunctionCall(
        const Token& nameToken, 
        Arguments* arguments);

    [[nodiscard]] const Token& name() noexcept { return m_nameToken; }
    [[nodiscard]] Arguments* arguments() { return m_arguments; }

private:
    Token m_nameToken;
    Arguments* m_arguments;
};
