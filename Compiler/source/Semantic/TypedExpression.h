#pragma once

#include <Defines.h>
#include <Semantic/TypedNode.h>

class COMPILER_API TypedExpression : public TypedNode
{
public:
    TypedExpression(Node* source, NodeKind kind, Type type);
};
