#pragma once

#include <Defines.h>
#include <Compiler/DiagnosticsBag.h>
#include <Semantic/Environment.h>
#include <Semantic/Type.h>
#include <Semantic/TypeCheckerOptions.h>
#include <Semantic/TypeDatabase.h>
#include <Semantic/TypedExpression.h>
#include <Semantic/TypedNode.h>
#include <Semantic/TypedStatement.h>
#include <Semantic/TypedTree.h>
#include <Syntax/AssignmentStatement.h>
#include <Syntax/FunctionCallExpression.h>
#include <Syntax/NameExpression.h>
#include <Syntax/DiscardLiteral.h>
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
    TypedExpression* TypeCheckNameExpression(NameExpression* expression);
    TypedExpression* TypeCheckDiscardLiteral(DiscardLiteral* literal);
    TypedExpression* TypeCheckNumberLiteral(NumberLiteral* literal);
    TypedExpression* TypeCheckFunctionCallExpression(FunctionCallExpression* functionCallExpression);

    Type inferType(TypedNode* node);

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
