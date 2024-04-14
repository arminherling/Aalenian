#pragma once

#include <Defines.h>
#include <Compiler/DiagnosticsBag.h>
#include <Semantic/Environment.h>
#include <Semantic/Type.h>
#include <Semantic/TypeCheckerOptions.h>
#include <Semantic/TypeDatabase.h>
#include <Semantic/TypedFieldDefinitionNode.h>
#include <Semantic/TypedExpression.h>
#include <Semantic/TypedNode.h>
#include <Semantic/TypedStatement.h>
#include <Semantic/TypedTree.h>
#include <Syntax/AssignmentStatement.h>
#include <Syntax/BinaryExpression.h>
#include <Syntax/DiscardLiteral.h>
#include <Syntax/EnumDefinitionStatement.h>
#include <Syntax/FunctionCallExpression.h>
#include <Syntax/FunctionDefinitionStatement.h>
#include <Syntax/GroupingExpression.h>
#include <Syntax/NameExpression.h>
#include <Syntax/NumberLiteral.h>
#include <Syntax/ParseTree.h>
#include <Syntax/TypeDefinitionStatement.h>
#include <Syntax/UnaryExpression.h>

class COMPILER_API TypeChecker
{
public:
    TypeChecker(
        const ParseTree& parseTree, 
        const TypeCheckerOptions& options, 
        Environment& environment, 
        TypeDatabase& typeDatabase, 
        DiagnosticsBag& diagnostics);

    TypedTree typeCheck();

private:
    [[nodiscard]] TypedStatement* typeCheckStatement(Statement* statement);
    [[nodiscard]] TypedExpression* typeCheckExpression(Expression* expression);

    [[nodiscard]] TypedStatement* typeCheckAssignmentStatement(AssignmentStatement* statement);
    [[nodiscard]] TypedStatement* typeCheckEnumDefinitionStatement(EnumDefinitionStatement* statement);
    [[nodiscard]] TypedStatement* typeCheckTypeDefinitionStatement(TypeDefinitionStatement* statement);
    [[nodiscard]] TypedStatement* typeCheckFunctionDefinitionStatement(FunctionDefinitionStatement* statement);
    [[nodiscard]] QList<TypedFieldDefinitionNode*> typeCheckEnumFieldDefinitionNodes(
        Type newType, 
        Type baseType, 
        const QList<EnumFieldDefinitionStatement*>& fieldDefinitions);
    [[nodiscard]] QList<TypedFieldDefinitionNode*> typeCheckTypeFieldDefinitionNodes(Type newType, BlockNode* body);
    [[nodiscard]] TypedExpression* typeCheckUnaryExpressionExpression(UnaryExpression* unaryExpression);
    [[nodiscard]] TypedExpression* typeCheckBinaryExpressionExpression(BinaryExpression* binaryExpression);
    [[nodiscard]] TypedExpression* typeCheckFunctionCallExpression(FunctionCallExpression* functionCallExpression); 
    [[nodiscard]] TypedExpression* typeCheckNameExpression(NameExpression* expression);
    [[nodiscard]] TypedExpression* typeCheckGroupingExpression(GroupingExpression* expression);
    [[nodiscard]] TypedExpression* typeCheckDiscardLiteral(DiscardLiteral* literal);
    [[nodiscard]] TypedExpression* typeCheckNumberLiteral(NumberLiteral* literal);

    [[nodiscard]] Type inferType(TypedNode* node);
    [[nodiscard]] Type convertTypeNameToType(const TypeName& typeName);
    [[nodiscard]] std::tuple<TypedExpression*, i32> convertValueToTypedLiteral(QStringView literal, Type type, Node* source);
    [[nodiscard]] std::tuple<TypedExpression*, i32> convertValueToTypedLiteral(i32 value, Type type, Node* source);

    ParseTree m_parseTree;
    TypeCheckerOptions m_options;
    Environment& m_environment; 
    TypeDatabase& m_typeDatabase;
    DiagnosticsBag& m_diagnostics;
};

COMPILER_API TypedTree TypeCheck(
    const ParseTree& parseTree, 
    const TypeCheckerOptions& options, 
    Environment& environment, 
    TypeDatabase& typeDatabase, 
    DiagnosticsBag& diagnostics) noexcept;
