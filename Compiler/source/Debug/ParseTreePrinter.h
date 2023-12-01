#pragma once

#include <Defines.h>
#include <Syntax/ParseTree.h>
#include <Syntax/Node.h>

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
    void PrettyPrintEnumMember(EnumMember* statement);
    void PrettyPrintTypeDefinitionStatement(TypeDefinitionStatement* statement);
    void PrettyPrintFieldDeclarationStatement(FieldDeclarationStatement* statement);
    void PrettyPrintMethodDefinitionStatement(MethodDefinitionStatement* statement);
    void PrettyPrintIfStatement(IfStatement* statement);
    void PrettyPrintWhileStatement(WhileStatement* statement);
    void PrettyPrintReturnStatement(ReturnStatement* statement);
    void PrettyPrintArgument(Argument* argument);
    void PrettyPrintArguments(Arguments* arguments);
    void PrettyPrintParameter(Parameter* parameter);
    void PrettyPrintParameters(Parameters* parameters);
    void PrettyPrintBlock(Block* block);

    void PrettyPrintDiscard(Discard* discard);
    void PrettyPrintFunctionCall(FunctionCall* functionCall);
    void PrettyPrintType(const Type& type);
    void PrettyPrintBool(Bool* node);
    void PrettyPrintName(Name* name);
    void PrettyPrintNumber(Number* number);
    void PrettyPrintGrouping(Grouping* grouping);
    void PrettyPrintUnaryExpression(UnaryExpression* unaryExpression);
    void PrettyPrintBinaryExpression(BinaryExpression* binaryExpression);
    void PrettyPrintMemberAccess(MemberAccess* memberAccess);
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
