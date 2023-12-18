#pragma once

#include <Defines.h>
#include <Syntax/NodeKind.h>

class COMPILER_API Node
{
public:
    Node(NodeKind kind);

    NodeKind kind() { return m_kind; }

private:
    NodeKind m_kind;
};
