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
    EnumMemberDefinitionStatement,
    TypeDefinitionStatement,
    FieldDeclarationStatement,
    MethodDefinitionStatement,
    IfStatement,
    WhileStatement,
    ReturnStatement,

    UnaryExpression,
    BinaryExpression,
    FunctionCallExpression,
    NameExpression,
    GroupingExpression,
    ScopeAccessExpression,
    MemberAccessExpression,

    DiscardLiteral,
    BoolLiteral,
    NumberLiteral,

    TypeNode,
    ParameterNode,
    ParametersNode,
    ArgumentNode,
    ArgumentsNode,
    BlockNode
};

COMPILER_API QString StringifyNodeKind(NodeKind kind);
