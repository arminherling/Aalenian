#pragma once

#include <Compiler/API.h>
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
    FieldDefinitionStatement,
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
    TypedFunctionDefinitionStatement,
    TypedEnumDefinitionStatement,
    TypedFieldDefinitionNode,
    TypedTypeDefinitionStatement,
    TypedMethodDefinitionStatement,
    TypedIfStatement,
    TypedWhileStatement,
    TypedReturnStatement,

    TypedReferenceOfExpression,
    TypedNegationExpression,
    TypedEnumValueAccessExpression,
    TypedFieldAccessExpression,
    TypedAdditionExpression,
    TypedSubtractionExpression,
    TypedMultiplicationExpression,
    TypedDivisionExpression,
    TypedFunctionCallExpression,
    TypedMethodCallExpression,

    TypedConstant,
    TypedVariable,
    Discard,
    BoolValue,
    U8Value,
    I32Value,

    Parameter
};

COMPILER_API [[nodiscard]] QString StringifyNodeKind(NodeKind kind);
