#include <Debug/ParseTreePrinter.h>

ParseTreePrinter::ParseTreePrinter(ParseTree& parseTree, int indentation)
    : m_parseTree{ parseTree }
    , m_indentation{ indentation }
    , m_indentationLevel{ 0 }
    , m_output{ QString() }
    , m_stream{ &m_output }
{
}

QString ParseTreePrinter::PrettyPrint()
{
    for (const auto& globalStatement : m_parseTree.GlobalStatements())
    {
        PrettyPrintNode(globalStatement);
    }

    return toUtf8();
}

void ParseTreePrinter::PrettyPrintNode(Node* node)
{
    switch (node->Kind())
    {
        case NodeKind::AssignmentStatement:
        {
            PrettyPrintAssignmentStatement((AssignmentStatement*)node);
            break;
        }
        case NodeKind::ExpressionStatement:
        {
            PrettyPrintExpressionStatement((ExpressionStatement*)node);
            break;
        }
        case NodeKind::FunctionDefinitionStatement:
        {
            PrettyPrintFunctionDefinitionStatement((FunctionDefinitionStatement*)node);
            break;
        }
        case NodeKind::TypeDefinitionStatement:
        {
            PrettyPrintTypeDefinitionStatement((TypeDefinitionStatement*)node);
            break;
        }
        case NodeKind::FieldDeclarationStatement:
        {
            PrettyPrintFieldDeclarationStatement((FieldDeclarationStatement*)node);
            break;
        }
        case NodeKind::MethodDefinitionStatement:
        {
            PrettyPrintMethodDefinitionStatement((MethodDefinitionStatement*)node);
            break;
        }
        case NodeKind::ReturnStatement:
        {
            PrettyPrintReturnStatement((ReturnStatement*)node);
            break;
        }
        case NodeKind::Discard:
        {
            PrettyPrintDiscard((Discard*)node);
            break;
        }
        case NodeKind::FunctionCall:
        {
            PrettyPrintFunctionCall((FunctionCall*)node);
            break;
        }
        case NodeKind::Name:
        {
            PrettyPrintName((Name*)node);
            break;
        }
        case NodeKind::Number:
        {
            PrettyPrintNumber((Number*)node);
            break;
        }
        case NodeKind::Error:
        {
            PrettyPrintError((Error*)node);
            break;
        }
        default:
            stream() << Indentation() << QString("Missing NodeKind!!") << NewLine();
            break;
    }
}

void ParseTreePrinter::PrettyPrintAssignmentStatement(AssignmentStatement* statement)
{
    stream() << Indentation() << StringifyNodeKind(statement->Kind()) << QString(": {") << NewLine();
    PushIndentation();
    
    stream() << Indentation() << QString("Left: {") << NewLine();
    PushIndentation();
    PrettyPrintNode(statement->LeftExpression());
    PopIndentation();
    stream() << Indentation() << QString("}") << NewLine();

    stream() << Indentation() << QString("Right: {") << NewLine();
    PushIndentation();
    PrettyPrintNode(statement->RightExpression());
    PopIndentation();
    stream() << Indentation() << QString("}") << NewLine();

    PopIndentation();
    stream() << Indentation() << QString("}") << NewLine();
}

void ParseTreePrinter::PrettyPrintExpressionStatement(ExpressionStatement* statement)
{
    stream() << Indentation() << StringifyNodeKind(statement->Kind()) << QString(": {") << NewLine();

    PushIndentation();
    PrettyPrintNode(statement->expression());
    PopIndentation();
    stream() << Indentation() << QString("}") << NewLine();
}

void ParseTreePrinter::PrettyPrintFunctionDefinitionStatement(FunctionDefinitionStatement* statement)
{
    auto nameToken = statement->name();
    auto nameLexeme = m_parseTree.Tokens().GetLexeme(nameToken.kindIndex);

    stream() << Indentation() << StringifyNodeKind(statement->Kind()) << QString(": {") << NewLine();
    PushIndentation();
    stream() << Indentation() << QString("Name: %1").arg(nameLexeme) << NewLine();
    PrettyPrintParameters(statement->parameters());
    PrettyPrintBlock(statement->body());
    PopIndentation();
    stream() << Indentation() << QString("}") << NewLine();
}

void ParseTreePrinter::PrettyPrintTypeDefinitionStatement(TypeDefinitionStatement* statement)
{
    auto nameToken = statement->name();
    auto nameLexeme = m_parseTree.Tokens().GetLexeme(nameToken.kindIndex);

    stream() << Indentation() << StringifyNodeKind(statement->Kind()) << QString(": {") << NewLine();
    PushIndentation();
    stream() << Indentation() << QString("Name: %1").arg(nameLexeme) << NewLine();
    PrettyPrintBlock(statement->body());
    PopIndentation();
    stream() << Indentation() << QString("}") << NewLine();
}

void ParseTreePrinter::PrettyPrintFieldDeclarationStatement(FieldDeclarationStatement* statement)
{
    stream() << Indentation() << StringifyNodeKind(statement->Kind()) << QString(": {") << NewLine();
    PushIndentation();

    stream() << Indentation() << QString("Field: {") << NewLine();
    PushIndentation();
    PrettyPrintNode(statement->name());
    PopIndentation();
    stream() << Indentation() << QString("}") << NewLine();

    if (statement->type().has_value())
        stream() << Indentation() << QString("Type: ") << StringifyType(statement->type().value()) << NewLine();

    if (statement->expression().has_value())
    {
        stream() << Indentation() << QString("Value: {") << NewLine();
        PushIndentation();
        PrettyPrintNode(statement->expression().value());
        PopIndentation();
        stream() << Indentation() << QString("}") << NewLine();
    }

    PopIndentation();
    stream() << Indentation() << QString("}") << NewLine();
}

void ParseTreePrinter::PrettyPrintMethodDefinitionStatement(MethodDefinitionStatement* statement)
{
    auto nameToken = statement->name();
    auto nameLexeme = m_parseTree.Tokens().GetLexeme(nameToken.kindIndex);

    stream() << Indentation() << StringifyNodeKind(statement->Kind()) << QString(": {") << NewLine();
    PushIndentation();
    stream() << Indentation() << QString("Name: %1").arg(nameLexeme) << NewLine();
    PrettyPrintParameters(statement->parameters());
    PrettyPrintBlock(statement->body());
    PopIndentation();
    stream() << Indentation() << QString("}") << NewLine();
}

void ParseTreePrinter::PrettyPrintReturnStatement(ReturnStatement* statement)
{
    stream() << Indentation() << StringifyNodeKind(statement->Kind()) << QString(": {") << NewLine();
    PushIndentation();
    PrettyPrintNode(statement->expression());
    PopIndentation();
    stream() << Indentation() << QString("}") << NewLine();
}

void ParseTreePrinter::PrettyPrintArguments(Arguments* arguments)
{
    stream() << Indentation() << StringifyNodeKind(arguments->Kind()) << QString("(0): {") << NewLine();

    PushIndentation();


    PopIndentation();
    stream() << Indentation() << QString("}") << NewLine();
}

void ParseTreePrinter::PrettyPrintParameters(Parameters* parameters)
{
    stream() << Indentation() << StringifyNodeKind(parameters->Kind()) << QString("(0): {") << NewLine();

    PushIndentation();


    PopIndentation();
    stream() << Indentation() << QString("}") << NewLine();
}

void ParseTreePrinter::PrettyPrintBlock(Block* block)
{
    auto& statements = block->Statements();
    stream() << Indentation() << StringifyNodeKind(block->Kind()) << QString("(%1): {").arg(statements.size()) << NewLine();
    PushIndentation();

    for (const auto& statement : block->Statements())
        PrettyPrintNode(statement);

    PopIndentation();
    stream() << Indentation() << QString("}") << NewLine();
}

void ParseTreePrinter::PrettyPrintDiscard(Discard* discard)
{
    stream() << Indentation() << StringifyNodeKind(discard->Kind()) << ": _" << NewLine();
}

void ParseTreePrinter::PrettyPrintFunctionCall(FunctionCall* functionCall)
{
    auto nameToken = functionCall->Name();
    auto nameLexeme = m_parseTree.Tokens().GetLexeme(nameToken.kindIndex);
    stream() << Indentation() << StringifyNodeKind(functionCall->Kind()) << QString(": {") << NewLine();

    PushIndentation();
    stream() << Indentation() << QString("Name: %1").arg(nameLexeme) << NewLine();
    PrettyPrintArguments(functionCall->arguments());
    PopIndentation();
    stream() << Indentation() << QString("}") << NewLine();
}

QString ParseTreePrinter::StringifyType(Name* name)
{
    auto token = name->Identifier();
    auto lexeme = m_parseTree.Tokens().GetLexeme(token.kindIndex);
    return lexeme.toString();
}

void ParseTreePrinter::PrettyPrintName(Name* name)
{
    auto token = name->Identifier();
    auto lexeme = m_parseTree.Tokens().GetLexeme(token.kindIndex);
    stream() << Indentation() << StringifyNodeKind(name->Kind()) << QString(": %1").arg(lexeme) << NewLine();
}

void ParseTreePrinter::PrettyPrintNumber(Number* number)
{
    auto token = number->token();
    auto lexeme = m_parseTree.Tokens().GetLexeme(token.kindIndex);
    stream() << Indentation() << StringifyNodeKind(number->Kind()) << QString(": %1").arg(lexeme) << NewLine();

    auto optionalType = number->type();
    if (!optionalType.has_value())
        return;

    auto type = optionalType.value();
    stream() << Indentation() << QString("Type: ") << StringifyType(type) << NewLine();
}

void ParseTreePrinter::PrettyPrintError(Error* error)
{
    stream() << Indentation() << QString("Error!!") << NewLine();
}
