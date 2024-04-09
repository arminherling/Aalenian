#pragma once

#include <Debug/BasePrinter.h>
#include <Defines.h>
#include <Semantic/Discard.h>
#include <Semantic/I32Literal.h>
#include <Semantic/TypedAssignmentStatement.h>
#include <Semantic/TypeDatabase.h>
#include <Semantic/TypedEnumDefinitionStatement.h>
#include <Semantic/TypedEnumFieldAccessExpression.h>
#include <Semantic/TypedFunctionCallExpression.h>
#include <Semantic/TypedGlobalValue.h>
#include <Semantic/TypedNegationExpression.h>
#include <Semantic/TypedNode.h>
#include <Semantic/TypedTree.h>
#include <Semantic/TypedTypeDefinitionStatement.h>
#include <Semantic/U8Literal.h>

class COMPILER_API TypedTreePrinter : public BasePrinter
{
public:
    TypedTreePrinter(TypedTree& typedTree, const TypeDatabase& typeDatabase, i32 indentation = 4);

    [[nodiscard]] QString PrettyPrint();

private:
    void PrettyPrintNode(TypedNode* node);

    void PrettyPrintTypedAssignmentStatement(TypedAssignmentStatement* statement);
    void PrettyPrintTypedEnumDefinitionStatement(TypedEnumDefinitionStatement* statement);
    void PrettyPrintTypedTypeDefinitionStatement(TypedTypeDefinitionStatement* statement);
    void PrettyPrintTypedNegationExpression(TypedNegationExpression* expression);
    void PrettyPrintTypedEnumFieldAccessExpression(TypedEnumFieldAccessExpression* expression);
    void PrettyPrintTypedGlobalValue(TypedGlobalValue* value);
    void PrettyPrintTypedFunctionCallExpression(TypedFunctionCallExpression* functionCall);
    void PrettyPrintDiscard(Discard* discard);
    void PrettyPrintU8Literal(U8Literal* literal);
    void PrettyPrintI32Literal(I32Literal* literal);

    void PrettyPrintTypedFieldDefinitionNode(TypedFieldDefinitionNode* field);
    void PrettyPrintTypedArgumentsNode();
    [[nodiscard]] QString PrettyPrintType(Type type) noexcept;

    TypedTree& m_typedTree;
    TypeDatabase m_typeDatabase;
};
