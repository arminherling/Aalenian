#pragma once

#include <Debug/BasePrinter.h>
#include <Defines.h>
#include <Semantic/I32Literal.h>
#include <Semantic/TypedAssignmentStatement.h>
#include <Semantic/TypeDatabase.h>
#include <Semantic/TypedFunctionCallExpression.h>
#include <Semantic/TypedGlobalValue.h>
#include <Semantic/TypedNode.h>
#include <Semantic/TypedTree.h>

class COMPILER_API TypedTreePrinter : public BasePrinter
{
public:
    TypedTreePrinter(TypedTree& typedTree, const TypeDatabase& typeDatabase, i32 indentation = 4);

    QString PrettyPrint();

private:
    void PrettyPrintNode(TypedNode* node);

    void PrettyPrintTypedAssignmentStatement(TypedAssignmentStatement* statement);
    void PrettyPrintTypedGlobalValue(TypedGlobalValue* value);
    void PrettyPrintTypedFunctionCallExpression(TypedFunctionCallExpression* functionCall);
    void PrettyPrintI32Literal(I32Literal* literal);

    void PrettyPrintTypedArgumentsNode();
    QString PrettyPrintType(Type type);

    TypedTree& m_typedTree;
    TypeDatabase m_typeDatabase;
};
