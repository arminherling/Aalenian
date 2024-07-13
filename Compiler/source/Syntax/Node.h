#pragma once

#include <Compiler/API.h>
#include <Syntax/NodeKind.h>

class COMPILER_API Node
{
public:
    Node(NodeKind kind);

    [[nodiscard]] NodeKind kind() const noexcept { return m_kind; }

private:
    NodeKind m_kind;
};
