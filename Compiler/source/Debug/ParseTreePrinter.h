#pragma once

#include <Debug/BasePrinter.h>
#include <Defines.h>
#include <Syntax/ArgumentNode.h>
#include <Syntax/ArgumentsNode.h>
#include <Syntax/AssignmentStatement.h>
#include <Syntax/BinaryExpression.h>
#include <Syntax/BlockNode.h>
#include <Syntax/BoolLiteral.h>
#include <Syntax/DiscardLiteral.h>
#include <Syntax/EnumDefinitionStatement.h>
#include <Syntax/EnumMemberDefinitionStatement.h>
#include <Syntax/Error.h>
#include <Syntax/ExpressionStatement.h>
#include <Syntax/FieldDeclarationStatement.h>
#include <Syntax/FunctionCallExpression.h>
#include <Syntax/FunctionDefinitionStatement.h>
#include <Syntax/GroupingExpression.h>
#include <Syntax/IfStatement.h>
#include <Syntax/MemberAccessExpression.h>
#include <Syntax/MethodDefinitionStatement.h>
#include <Syntax/NameExpression.h>
#include <Syntax/NumberLiteral.h>
#include <Syntax/ParameterNode.h>
#include <Syntax/ParametersNode.h>
#include <Syntax/ParseTree.h>
#include <Syntax/ReturnStatement.h>
#include <Syntax/TypeDefinitionStatement.h>
#include <Syntax/TypeName.h>
#include <Syntax/UnaryExpression.h>
#include <Syntax/WhileStatement.h>

class COMPILER_API ParseTreePrinter : public BasePrinter
{
public:
    ParseTreePrinter(ParseTree& parseTree, i32 indentation = 4);

    QString PrettyPrint();

private:
    void PrettyPrintNode(Node* node);
    void PrettyPrintAssignmentStatement(AssignmentStatement* statement);
    void PrettyPrintExpressionStatement(ExpressionStatement* statement);
    void PrettyPrintFunctionDefinitionStatement(FunctionDefinitionStatement* statement);
    void PrettyPrintEnumDefinitionStatement(EnumDefinitionStatement* statement);
    void PrettyPrintEnumMemberDefinitionStatement(EnumMemberDefinitionStatement* statement);
    void PrettyPrintTypeDefinitionStatement(TypeDefinitionStatement* statement);
    void PrettyPrintFieldDeclarationStatement(FieldDeclarationStatement* statement);
    void PrettyPrintMethodDefinitionStatement(MethodDefinitionStatement* statement);
    void PrettyPrintIfStatement(IfStatement* statement);
    void PrettyPrintWhileStatement(WhileStatement* statement);
    void PrettyPrintReturnStatement(ReturnStatement* statement);
    void PrettyPrintArgumentNode(ArgumentNode* argument);
    void PrettyPrintArgumentsNode(ArgumentsNode* arguments);
    void PrettyPrintParameterNode(ParameterNode* parameter);
    void PrettyPrintParametersNode(ParametersNode* parameters);
    void PrettyPrintBlockNode(BlockNode* block);

    void PrettyPrintDiscardLiteral(DiscardLiteral* discard);
    void PrettyPrintFunctionCallExpression(FunctionCallExpression* functionCall);
    void PrettyPrintTypeName(const TypeName& type);
    void PrettyPrintBoolLiteral(BoolLiteral* node);
    void PrettyPrintNameExpression(NameExpression* name);
    void PrettyPrintNumberLiteral(NumberLiteral* number);
    void PrettyPrintGroupingExpression(GroupingExpression* grouping);
    void PrettyPrintUnaryExpression(UnaryExpression* unaryExpression);
    void PrettyPrintBinaryExpression(BinaryExpression* binaryExpression);
    void PrettyPrintMemberAccessExpression(MemberAccessExpression* memberAccess);
    void PrettyPrintError(Error* error);

    ParseTree& m_parseTree;
};
