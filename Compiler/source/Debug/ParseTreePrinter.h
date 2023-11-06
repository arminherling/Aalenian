#pragma once

#include <API.h>
#include <Syntax/ParseTree.h>
#include <Syntax/Node.h>

#include <qtextstream.h>

class COMPILER_API ParseTreePrinter
{
public:
    ParseTreePrinter(ParseTree& parseTree, int indentation = 4);

    QString PrettyPrint();

private:
    void PrettyPrintNode(Node* node);
    void PrettyPrintAssignmentStatement(AssignmentStatement* statement);
    void PrettyPrintExpressionStatement(ExpressionStatement* statement);
    void PrettyPrintFunctionDefinitionStatement(FunctionDefinitionStatement* statement);
    void PrettyPrintTypeDefinitionStatement(TypeDefinitionStatement* statement);
    void PrettyPrintFieldDeclarationStatement(FieldDeclarationStatement* statement);
    void PrettyPrintMethodDefinitionStatement(MethodDefinitionStatement* statement);
    void PrettyPrintReturnStatement(ReturnStatement* statement);
    void PrettyPrintArguments(Arguments* arguments);
    void PrettyPrintParameters(Parameters* parameters);
    void PrettyPrintBlock(Block* block);

    void PrettyPrintDiscard(Discard* discard);
    void PrettyPrintFunctionCall(FunctionCall* functionCall);
    void PrettyPrintName(Name* name);
    void PrettyPrintNumber(Number* number);
    void PrettyPrintGrouping(Grouping* grouping);
    void PrettyPrintMemberAccess(MemberAccess* memberAccess);
    void PrettyPrintError(Error* error);

    void PushIndentation() { m_indentationLevel++; }
    void PopIndentation() { m_indentationLevel--; }
    QTextStream& stream() { return m_stream; }
    QByteArray toUtf8() { return m_output.toUtf8(); }

    QString StringifyType(Name* name);
    QString Indentation() { return QString(" ").repeated(m_indentation * m_indentationLevel); }
    QString NewLine() { return QString("\r\n"); }

    int m_indentation;
    int m_indentationLevel;
    ParseTree& m_parseTree;
    QString m_output;
    QTextStream m_stream;
};

