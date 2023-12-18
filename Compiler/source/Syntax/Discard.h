#pragma once

#include <Defines.h>
#include <Syntax/Expression.h>
#include <Syntax/Token.h>

class COMPILER_API Discard : public Expression
{
public:
    Discard(const Token& token);
};
