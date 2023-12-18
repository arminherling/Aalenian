#pragma once

#include <Defines.h>
#include <Syntax/Expression.h>
#include <Syntax/Token.h>

class COMPILER_API DiscardLiteral : public Expression
{
public:
    DiscardLiteral(const Token& token);
};
