#pragma once

#include <Debug/BasePrinter.h>
#include <Defines.h>
#include <Semantic/Discard.h>
#include <Semantic/I32Value.h>
#include <Semantic/Parameter.h>
#include <Semantic/TypedAssignmentStatement.h>
#include <Semantic/TypeDatabase.h>
#include <Semantic/TypedBinaryExpression.h>
#include <Semantic/TypedConstant.h>
#include <Semantic/TypedEnumDefinitionStatement.h>
#include <Semantic/TypedEnumFieldAccessExpression.h>
#include <Semantic/TypedExpressionStatement.h>
#include <Semantic/TypedFunctionCallExpression.h>
#include <Semantic/TypedFunctionDefinitionStatement.h>
#include <Semantic/TypedNegationExpression.h>
#include <Semantic/TypedNode.h>
#include <Semantic/TypedReturnStatement.h>
#include <Semantic/TypedTree.h>
#include <Semantic/TypedTypeDefinitionStatement.h>
#include <Semantic/TypedVariable.h>
#include <Semantic/U8Value.h>
#include <Semantic/BoolValue.h>

class COMPILER_API TypedTreePrinter : public BasePrinter
{
public:
    TypedTreePrinter(TypedTree& typedTree, const TypeDatabase& typeDatabase, i32 indentation = 4);

    [[nodiscard]] QString PrettyPrint();

private:
    void PrettyPrintNode(TypedNode* node);

    void PrettyPrintTypedAssignmentStatement(TypedAssignmentStatement* statement);
    void PrettyPrintTypedExpressionStatement(TypedExpressionStatement* statement);
    void PrettyPrintTypedEnumDefinitionStatement(TypedEnumDefinitionStatement* statement);
    void PrettyPrintTypedTypeDefinitionStatement(TypedTypeDefinitionStatement* statement);
    void PrettyPrintTypedFunctionDefinitionStatement(TypedFunctionDefinitionStatement* statement);
    void PrettyPrintTypedReturnStatement(TypedReturnStatement* statement);
    void PrettyPrintTypedNegationExpression(TypedNegationExpression* expression);
    void PrettyPrintTypedEnumFieldAccessExpression(TypedEnumFieldAccessExpression* expression);
    void PrettyPrintTypedBinaryExpression(TypedBinaryExpression* expression);
    void PrettyPrintTypedConstant(TypedConstant* constant);
    void PrettyPrintTypedVariable(TypedVariable* variable);
    void PrettyPrintParameter(Parameter* parameter);
    void PrettyPrintTypedFunctionCallExpression(TypedFunctionCallExpression* functionCall);
    void PrettyPrintDiscard(Discard* discard);
    void PrettyPrintBoolValue(BoolValue* value);
    void PrettyPrintU8Value(U8Value* value);
    void PrettyPrintI32Value(I32Value* value);

    void PrettyPrintTypedFieldDefinitionNode(TypedFieldDefinitionNode* field);
    void PrettyPrintTypedArgumentsNode();
    [[nodiscard]] QString PrettyPrintType(Type type) noexcept;

    TypedTree& m_typedTree;
    TypeDatabase m_typeDatabase;
};
