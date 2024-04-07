#pragma once

#include <Defines.h>
#include <Compiler/DiagnosticsBag.h>
#include <Semantic/Environment.h>
#include <Semantic/Type.h>
#include <Semantic/TypeCheckerOptions.h>
#include <Semantic/TypeDatabase.h>
#include <Semantic/TypedEnumFieldDefinitionNode.h>
#include <Semantic/TypedExpression.h>
#include <Semantic/TypedNode.h>
#include <Semantic/TypedStatement.h>
#include <Semantic/TypedTree.h>
#include <Syntax/AssignmentStatement.h>
#include <Syntax/BinaryExpression.h>
#include <Syntax/DiscardLiteral.h>
#include <Syntax/EnumDefinitionStatement.h>
#include <Syntax/FunctionCallExpression.h>
#include <Syntax/NameExpression.h>
#include <Syntax/NumberLiteral.h>
#include <Syntax/ParseTree.h>

class COMPILER_API TypeChecker
{
public:
    TypeChecker(
        const ParseTree& parseTree, 
        const TypeCheckerOptions& options, 
        Environment& environment, 
        TypeDatabase& typeDatabase, 
        DiagnosticsBag& diagnostics);

    TypedTree TypeCheck();

private:
    [[nodiscard]] TypedStatement* TypeCheckStatement(Statement* statement);
    [[nodiscard]] TypedExpression* TypeCheckExpression(Expression* expression);

    [[nodiscard]] TypedStatement* TypeCheckAssignmentStatement(AssignmentStatement* statement);
    [[nodiscard]] TypedStatement* TypeCheckEnumDefinitionStatement(EnumDefinitionStatement* statement);
    [[nodiscard]] QList<TypedEnumFieldDefinitionNode*> TypeCheckEnumFieldDefinitionNodes(Type enumType, Type baseType, const QList<EnumFieldDefinitionStatement*> fieldDefinitions);
    [[nodiscard]] TypedExpression* TypeCheckBinaryExpressionExpression(BinaryExpression* binaryExpression);
    [[nodiscard]] TypedExpression* TypeCheckFunctionCallExpression(FunctionCallExpression* functionCallExpression); 
    [[nodiscard]] TypedExpression* TypeCheckNameExpression(NameExpression* expression);
    [[nodiscard]] TypedExpression* TypeCheckDiscardLiteral(DiscardLiteral* literal);
    [[nodiscard]] TypedExpression* TypeCheckNumberLiteral(NumberLiteral* literal);

    [[nodiscard]] Type inferType(TypedNode* node);
    [[nodiscard]] std::tuple<TypedExpression*, i32> ConvertValueToTypedLiteral(QStringView literal, Type type, Node* source);
    [[nodiscard]] std::tuple<TypedExpression*, i32> ConvertValueToTypedLiteral(i32 value, Type type, Node* source);

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
