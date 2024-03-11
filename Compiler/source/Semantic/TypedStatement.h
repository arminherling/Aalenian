#pragma once

#include <Defines.h>
#include <Semantic/TypedNode.h>

class COMPILER_API TypedStatement : public TypedNode
{
public:
    TypedStatement(Node* source, NodeKind kind, Type type);
};
