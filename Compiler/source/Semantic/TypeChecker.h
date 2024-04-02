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
    TypedStatement* TypeCheckStatement(Statement* statement);
    TypedExpression* TypeCheckExpression(Expression* expression);

    TypedStatement* TypeCheckAssignmentStatement(AssignmentStatement* statement);
    TypedStatement* TypeCheckEnumDefinitionStatement(EnumDefinitionStatement* statement);
    QList<TypedEnumFieldDefinitionNode*> TypeCheckEnumFieldDefinitionNodes(const QList<EnumFieldDefinitionStatement*> fieldDefinitions, Type baseType);
    TypedExpression* TypeCheckNameExpression(NameExpression* expression);
    TypedExpression* TypeCheckDiscardLiteral(DiscardLiteral* literal);
    TypedExpression* TypeCheckNumberLiteral(NumberLiteral* literal);
    TypedExpression* TypeCheckFunctionCallExpression(FunctionCallExpression* functionCallExpression);

    Type inferType(TypedNode* node);
    TypedExpression* ConvertValueToTypedLiteral(QStringView literal, Type type, Node* source);
    TypedExpression* ConvertValueToTypedLiteral(i32 value, Type type, Node* source);

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
