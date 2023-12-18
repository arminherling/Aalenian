#pragma once

#include <Defines.h>
#include <QString>

enum class COMPILER_API NodeKind
{
    Unknown,
    Error,

    AssignmentStatement,
    ExpressionStatement,
    FunctionDefinitionStatement,
    EnumDefinitionStatement,
    TypeDefinitionStatement,
    FieldDeclarationStatement,
    MethodDefinitionStatement,
    IfStatement,
    WhileStatement,
    ReturnStatement,

    UnaryExpression,
    BinaryExpression,
    Type,
    Parameter,
    Parameters,
    Argument,
    Arguments,
    Block,
    EnumMember,

    Discard,
    FunctionCall,
    Name,
    Bool,
    Number,
    Grouping,
    ScopeAccess,
    MemberAccess
};

COMPILER_API QString StringifyNodeKind(NodeKind kind);
