#pragma once

#include <Defines.h>
#include <Semantic/Type.h>
#include <Semantic/TypedExpression.h>

class COMPILER_API Discard : public TypedExpression
{
public:
    Discard(Node* source);
};
