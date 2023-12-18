#pragma once

#include <Defines.h>
#include <Syntax/ParseTree.h>
#include <Syntax/AssignmentStatement.h>
#include <Syntax/ExpressionStatement.h>
#include <Syntax/FunctionDefinitionStatement.h>
#include <Syntax/EnumDefinitionStatement.h>
#include <Syntax/EnumMemberDefinitionStatement.h>
#include <Syntax/TypeDefinitionStatement.h>
#include <Syntax/FieldDeclarationStatement.h>
#include <Syntax/MethodDefinitionStatement.h>
#include <Syntax/IfStatement.h>
#include <Syntax/WhileStatement.h>
#include <Syntax/ReturnStatement.h>
#include <Syntax/ArgumentNode.h>
#include <Syntax/ArgumentsNode.h>
#include <Syntax/ParameterNode.h>
#include <Syntax/Parameters.h>
#include <Syntax/DiscardLiteral.h>
#include <Syntax/FunctionCallExpression.h>
#include <Syntax/Type.h>
#include <Syntax/BoolLiteral.h>
#include <Syntax/NameExpression.h>
#include <Syntax/Number.h>
#include <Syntax/BlockNode.h>
#include <Syntax/GroupingExpression.h>
#include <Syntax/UnaryExpression.h>
#include <Syntax/BinaryExpression.h>
#include <Syntax/MemberAccessExpression.h>
#include <Syntax/Error.h>

#include <qtextstream.h>

class COMPILER_API ParseTreePrinter
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
    void PrettyPrintParameters(Parameters* parameters);
    void PrettyPrintBlockNode(BlockNode* block);

    void PrettyPrintDiscardLiteral(DiscardLiteral* discard);
    void PrettyPrintFunctionCallExpression(FunctionCallExpression* functionCall);
    void PrettyPrintType(const Type& type);
    void PrettyPrintBoolLiteral(BoolLiteral* node);
    void PrettyPrintNameExpression(NameExpression* name);
    void PrettyPrintNumber(Number* number);
    void PrettyPrintGroupingExpression(GroupingExpression* grouping);
    void PrettyPrintUnaryExpression(UnaryExpression* unaryExpression);
    void PrettyPrintBinaryExpression(BinaryExpression* binaryExpression);
    void PrettyPrintMemberAccessExpression(MemberAccessExpression* memberAccess);
    void PrettyPrintError(Error* error);

    void PushIndentation() { m_indentationLevel++; }
    void PopIndentation() { m_indentationLevel--; }
    QTextStream& stream() { return m_stream; }
    QByteArray toUtf8() { return m_output.toUtf8(); }

    QString Indentation() { return QString(" ").repeated(m_indentation * m_indentationLevel); }
    QString NewLine() { return QString("\r\n"); }

    i32 m_indentation;
    i32 m_indentationLevel;
    ParseTree& m_parseTree;
    QString m_output;
    QTextStream m_stream;
};
