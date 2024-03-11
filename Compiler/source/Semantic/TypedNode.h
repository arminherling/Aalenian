#pragma once

#include <Defines.h>
#include <Syntax/Node.h>
#include <Syntax/NodeKind.h>
#include <Semantic/Type.h>

class COMPILER_API TypedNode
{
public:
    TypedNode(Node* source, NodeKind kind, Type type);

    Node* source() { return m_source; }
    NodeKind kind() { return m_kind; }
    Type type() { return m_type; }
    void setType(Type type) { m_type = type; }

private:
    Node* m_source;
    NodeKind m_kind;
    Type m_type;
};
