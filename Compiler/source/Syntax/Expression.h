#pragma once

#include <Defines.h>
#include <Syntax/Node.h>

class COMPILER_API Expression : public Node
{
public:
    Expression(NodeKind kind);
};
