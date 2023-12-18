#pragma once

#include <Defines.h>
#include <Syntax/Expression.h>
#include <Syntax/Token.h>
#include <Syntax/ArgumentsNode.h>

class COMPILER_API FunctionCall : public Expression
{
public:
    FunctionCall(
        const Token& nameToken, 
        ArgumentsNode* arguments);

    [[nodiscard]] const Token& name() noexcept { return m_nameToken; }
    [[nodiscard]] ArgumentsNode* arguments() { return m_arguments; }

private:
    Token m_nameToken;
    ArgumentsNode* m_arguments;
};
