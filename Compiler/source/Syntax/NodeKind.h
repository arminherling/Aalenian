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
    EnumFieldDefinitionStatement,
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

    TypeName,
    ArgumentNode,
    ArgumentsNode,
    ParameterNode,
    ParametersNode,
    BlockNode,

    TypedAssignmentStatement,
    TypedEnumDefinitionStatement,
    TypedEnumFieldDefinitionNode,
    
    TypedFunctionCallExpression,

    TypedGlobalValue,
    Discard,
    U8Literal,
    I32Literal
};

COMPILER_API QString StringifyNodeKind(NodeKind kind);
