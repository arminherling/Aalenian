#pragma once

#include <Defines.h>
#include <Syntax/Node.h>

class COMPILER_API Statement : public Node
{
public:
    Statement(NodeKind kind);
};
