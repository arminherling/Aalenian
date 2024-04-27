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
    ArgumentsNode,
    ParameterNode,
    ParametersNode,
    BlockNode,

    TypedAssignmentStatement,
    TypedExpressionStatement,
    TypedEnumDefinitionStatement,
    TypedFieldDefinitionNode,
    TypedTypeDefinitionStatement,
    TypedFunctionDefinitionStatement,
    TypedReturnStatement,

    TypedReferenceOfExpression,
    TypedNegationExpression,
    TypedEnumFieldAccessExpression,
    TypedAdditionExpression,
    TypedSubtractionExpression,
    TypedMultiplicationExpression,
    TypedDivisionExpression,
    TypedFunctionCallExpression,

    TypedConstant,
    TypedVariable,
    Discard,
    BoolValue,
    U8Value,
    I32Value,

    Parameter
};

COMPILER_API [[nodiscard]] QString StringifyNodeKind(NodeKind kind);
