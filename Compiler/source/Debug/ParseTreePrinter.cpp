#include <Debug/ParseTreePrinter.h>

ParseTreePrinter::ParseTreePrinter(ParseTree& parseTree, i32 indentation)
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
    switch (node->kind())
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
        case NodeKind::EnumDefinitionStatement:
        {
            PrettyPrintEnumDefinitionStatement((EnumDefinitionStatement*)node);
            break;
        }
        case NodeKind::EnumMember:
        {
            PrettyPrintEnumMemberDefinitionStatement((EnumMemberDefinitionStatement*)node);
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
        case NodeKind::IfStatement:
        {
            PrettyPrintIfStatement((IfStatement*)node);
            break;
        }
        case NodeKind::WhileStatement:
        {
            PrettyPrintWhileStatement((WhileStatement*)node);
            break;
        }
        case NodeKind::ReturnStatement:
        {
            PrettyPrintReturnStatement((ReturnStatement*)node);
            break;
        }
        case NodeKind::Argument:
        {
            PrettyPrintArgumentNode((ArgumentNode*)node);
            break;
        }
        case NodeKind::Parameter:
        {
            PrettyPrintParameterNode((ParameterNode*)node);
            break;
        }
        case NodeKind::Discard:
        {
            PrettyPrintDiscardLiteral((DiscardLiteral*)node);
            break;
        }
        case NodeKind::FunctionCall:
        {
            PrettyPrintFunctionCallExpression((FunctionCallExpression*)node);
            break;
        }
        case NodeKind::Bool:
        {
            PrettyPrintBoolLiteral((BoolLiteral*)node);
            break;
        }
        case NodeKind::Name:
        {
            PrettyPrintNameExpression((NameExpression*)node);
            break;
        }
        case NodeKind::Number:
        {
            PrettyPrintNumber((Number*)node);
            break;
        }
        case NodeKind::Grouping:
        {
            PrettyPrintGroupingExpression((GroupingExpression*)node);
            break;
        }
        case NodeKind::UnaryExpression:
        {
            PrettyPrintUnaryExpression((UnaryExpression*)node);
            break;
        }
        case NodeKind::BinaryExpression:
        {
            PrettyPrintBinaryExpression((BinaryExpression*)node);
            break;
        }
        case NodeKind::MemberAccess:
        {
            PrettyPrintMemberAccessExpression((MemberAccessExpression*)node);
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
    stream() << Indentation() << StringifyNodeKind(statement->kind()) << QString(": {") << NewLine();
    PushIndentation();
    
    stream() << Indentation() << QString("Left: {") << NewLine();
    PushIndentation();
    PrettyPrintNode(statement->leftExpression());
    PopIndentation();
    stream() << Indentation() << QString("}") << NewLine();

    stream() << Indentation() << QString("Right: {") << NewLine();
    PushIndentation();
    PrettyPrintNode(statement->rightExpression());
    PopIndentation();
    stream() << Indentation() << QString("}") << NewLine();

    PopIndentation();
    stream() << Indentation() << QString("}") << NewLine();
}

void ParseTreePrinter::PrettyPrintExpressionStatement(ExpressionStatement* statement)
{
    stream() << Indentation() << StringifyNodeKind(statement->kind()) << QString(": {") << NewLine();

    PushIndentation();
    PrettyPrintNode(statement->expression());
    PopIndentation();
    stream() << Indentation() << QString("}") << NewLine();
}

void ParseTreePrinter::PrettyPrintFunctionDefinitionStatement(FunctionDefinitionStatement* statement)
{
    auto nameToken = statement->name();
    auto nameLexeme = m_parseTree.Tokens().GetLexeme(nameToken.kindIndex);

    stream() << Indentation() << StringifyNodeKind(statement->kind()) << QString(": {") << NewLine();
    PushIndentation();
    stream() << Indentation() << QString("Name: %1").arg(nameLexeme) << NewLine();
    PrettyPrintParameters(statement->parameters());
    PrettyPrintBlockNode(statement->body());
    PopIndentation();
    stream() << Indentation() << QString("}") << NewLine();
}

void ParseTreePrinter::PrettyPrintEnumDefinitionStatement(EnumDefinitionStatement* statement)
{
    auto nameToken = statement->name();
    auto nameLexeme = m_parseTree.Tokens().GetLexeme(nameToken.kindIndex);

    stream() << Indentation() << StringifyNodeKind(statement->kind()) << QString(": {") << NewLine();
    PushIndentation();
    stream() << Indentation() << QString("Name: %1").arg(nameLexeme) << NewLine();

    if (statement->baseType().has_value())
        PrettyPrintType(statement->baseType().value());

    PrettyPrintBlockNode(statement->body());
    PopIndentation();
    stream() << Indentation() << QString("}") << NewLine();
}

void ParseTreePrinter::PrettyPrintEnumMemberDefinitionStatement(EnumMemberDefinitionStatement* statement)
{
    auto nameToken = statement->name()->identifier();
    auto nameLexeme = m_parseTree.Tokens().GetLexeme(nameToken.kindIndex);

    stream() << Indentation() << StringifyNodeKind(statement->kind()) << QString(": {") << NewLine();
    PushIndentation();
    stream() << Indentation() << QString("Name: %1").arg(nameLexeme) << NewLine();

    if (statement->value().has_value())
    {
        PrettyPrintNode(statement->value().value());
    }

    PopIndentation();
    stream() << Indentation() << QString("}") << NewLine();
}

void ParseTreePrinter::PrettyPrintTypeDefinitionStatement(TypeDefinitionStatement* statement)
{
    auto nameToken = statement->name();
    auto nameLexeme = m_parseTree.Tokens().GetLexeme(nameToken.kindIndex);

    stream() << Indentation() << StringifyNodeKind(statement->kind()) << QString(": {") << NewLine();
    PushIndentation();
    stream() << Indentation() << QString("Name: %1").arg(nameLexeme) << NewLine();
    PrettyPrintBlockNode(statement->body());
    PopIndentation();
    stream() << Indentation() << QString("}") << NewLine();
}

void ParseTreePrinter::PrettyPrintFieldDeclarationStatement(FieldDeclarationStatement* statement)
{
    stream() << Indentation() << StringifyNodeKind(statement->kind()) << QString(": {") << NewLine();
    PushIndentation();

    stream() << Indentation() << QString("Field: {") << NewLine();
    PushIndentation();
    PrettyPrintNode(statement->name());
    PopIndentation();
    stream() << Indentation() << QString("}") << NewLine();

    if (statement->type().has_value())
        PrettyPrintType(statement->type().value());

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

    stream() << Indentation() << StringifyNodeKind(statement->kind()) << QString(": {") << NewLine();
    PushIndentation();
    stream() << Indentation() << QString("Name: %1").arg(nameLexeme) << NewLine();
    PrettyPrintParameters(statement->parameters());
    PrettyPrintBlockNode(statement->body());
    PopIndentation();
    stream() << Indentation() << QString("}") << NewLine();
}

void ParseTreePrinter::PrettyPrintIfStatement(IfStatement* statement)
{
    stream() << Indentation() << StringifyNodeKind(statement->kind()) << QString(": {") << NewLine();
    PushIndentation();

    stream() << Indentation() << QString("Condition: {") << NewLine();
    PushIndentation();
    PrettyPrintNode(statement->condition());
    PopIndentation();
    stream() << Indentation() << QString("}") << NewLine();

    PrettyPrintBlockNode(statement->body());

    PopIndentation();
    stream() << Indentation() << QString("}") << NewLine();
}

void ParseTreePrinter::PrettyPrintWhileStatement(WhileStatement* statement)
{
    stream() << Indentation() << StringifyNodeKind(statement->kind()) << QString(": {") << NewLine();
    PushIndentation();

    stream() << Indentation() << QString("Condition: {") << NewLine();
    PushIndentation();
    PrettyPrintNode(statement->condition());
    PopIndentation();
    stream() << Indentation() << QString("}") << NewLine();

    PrettyPrintBlockNode(statement->body());

    PopIndentation();
    stream() << Indentation() << QString("}") << NewLine();
}

void ParseTreePrinter::PrettyPrintReturnStatement(ReturnStatement* statement)
{
    stream() << Indentation() << StringifyNodeKind(statement->kind()) << QString(": {") << NewLine();
    PushIndentation();

    if(statement->expression().has_value())
        PrettyPrintNode(statement->expression().value());

    PopIndentation();
    stream() << Indentation() << QString("}") << NewLine();
}

void ParseTreePrinter::PrettyPrintArgumentNode(ArgumentNode* argument)
{
    stream() << Indentation() << StringifyNodeKind(argument->kind()) << QString(": {") << NewLine();
    PushIndentation();

    if (argument->isReference())
        stream() << Indentation() << QString("Ref: true") << NewLine();

    PrettyPrintNode(argument->expression());

    PopIndentation();
    stream() << Indentation() << QString("}") << NewLine();
}

void ParseTreePrinter::PrettyPrintArgumentsNode(ArgumentsNode* node)
{
    const auto& arguments = node->arguments();
    stream() << Indentation() << StringifyNodeKind(node->kind()) << QString("(%1): {").arg(arguments.size()) << NewLine();
    PushIndentation();

    for (const auto& argument : arguments)
        PrettyPrintNode(argument);

    PopIndentation();
    stream() << Indentation() << QString("}") << NewLine();
}

void ParseTreePrinter::PrettyPrintParameterNode(ParameterNode* parameter)
{
    stream() << Indentation() << StringifyNodeKind(parameter->kind()) << QString(": {") << NewLine();
    PushIndentation();

    PrettyPrintNameExpression(parameter->name());
    PrettyPrintType(parameter->type());

    PopIndentation();
    stream() << Indentation() << QString("}") << NewLine();
}

void ParseTreePrinter::PrettyPrintParameters(Parameters* node)
{
    const auto& parameters = node->parameters();
    stream() << Indentation() << StringifyNodeKind(node->kind()) << QString("(%1): {").arg(parameters.size()) << NewLine();
    PushIndentation();

    for (const auto& parameter : parameters)
        PrettyPrintNode(parameter);

    PopIndentation();
    stream() << Indentation() << QString("}") << NewLine();
}

void ParseTreePrinter::PrettyPrintBlockNode(BlockNode* block)
{
    const auto& statements = block->statements();
    stream() << Indentation() << StringifyNodeKind(block->kind()) << QString("(%1): {").arg(statements.size()) << NewLine();
    PushIndentation();

    for (const auto& statement : block->statements())
        PrettyPrintNode(statement);

    PopIndentation();
    stream() << Indentation() << QString("}") << NewLine();
}

void ParseTreePrinter::PrettyPrintDiscardLiteral(DiscardLiteral* discard)
{
    stream() << Indentation() << StringifyNodeKind(discard->kind()) << ": _" << NewLine();
}

void ParseTreePrinter::PrettyPrintFunctionCallExpression(FunctionCallExpression* functionCall)
{
    auto nameToken = functionCall->name();
    auto nameLexeme = m_parseTree.Tokens().GetLexeme(nameToken.kindIndex);
    stream() << Indentation() << StringifyNodeKind(functionCall->kind()) << QString(": {") << NewLine();

    PushIndentation();
    stream() << Indentation() << QString("Name: %1").arg(nameLexeme) << NewLine();
    PrettyPrintArgumentsNode(functionCall->arguments());
    PopIndentation();
    stream() << Indentation() << QString("}") << NewLine();
}

void ParseTreePrinter::PrettyPrintType(const Type& type)
{
    auto token = type.name()->identifier();
    auto lexeme = m_parseTree.Tokens().GetLexeme(token.kindIndex);
    if (type.isReference())
        stream() << Indentation() << QString("Ref: true") << NewLine();

    stream() << Indentation() << QString("Type: ") << lexeme << NewLine();
}

void ParseTreePrinter::PrettyPrintBoolLiteral(BoolLiteral* node)
{
    auto value = node->value() ? QString("true") : QString("false");
    stream() << Indentation() << QString("Bool: ") << value << NewLine();
}

void ParseTreePrinter::PrettyPrintNameExpression(NameExpression* name)
{
    auto token = name->identifier();
    auto lexeme = m_parseTree.Tokens().GetLexeme(token.kindIndex);
    stream() << Indentation() << StringifyNodeKind(name->kind()) << QString(": %1").arg(lexeme) << NewLine();
}

void ParseTreePrinter::PrettyPrintNumber(Number* number)
{
    auto token = number->token();
    auto lexeme = m_parseTree.Tokens().GetLexeme(token.kindIndex);
    stream() << Indentation() << StringifyNodeKind(number->kind()) << QString(": %1").arg(lexeme) << NewLine();

    auto optionalType = number->type();
    if (!optionalType.has_value())
        return;

    PrettyPrintType(optionalType.value());
}

void ParseTreePrinter::PrettyPrintGroupingExpression(GroupingExpression* grouping)
{
    stream() << Indentation() << StringifyNodeKind(grouping->kind()) << QString(": {") << NewLine();
    PushIndentation();

    PrettyPrintNode(grouping->expression());

    PopIndentation();
    stream() << Indentation() << QString("}") << NewLine();
}

void ParseTreePrinter::PrettyPrintUnaryExpression(UnaryExpression* unaryExpression)
{
    stream() << Indentation() << StringifyNodeKind(unaryExpression->kind()) << QString(": {") << NewLine();
    PushIndentation();

    stream() << Indentation() << QString("Operation: ") << StringifyUnaryOperation(unaryExpression->unaryOperator().kind) << NewLine();

    stream() << Indentation() << QString("Expression: {") << NewLine();
    PushIndentation();
    PrettyPrintNode(unaryExpression->expression());
    PopIndentation();
    stream() << Indentation() << QString("}") << NewLine();

    PopIndentation();
    stream() << Indentation() << QString("}") << NewLine();
}

void ParseTreePrinter::PrettyPrintBinaryExpression(BinaryExpression* binaryExpression)
{
    stream() << Indentation() << StringifyNodeKind(binaryExpression->kind()) << QString(": {") << NewLine();
    PushIndentation();

    stream() << Indentation() << QString("Left: {") << NewLine();
    PushIndentation();
    PrettyPrintNode(binaryExpression->leftExpression());
    PopIndentation();
    stream() << Indentation() << QString("}") << NewLine();

    stream() << Indentation() << QString("Operation: ") << StringifyBinaryOperation(binaryExpression->binaryOperator().kind) << NewLine();

    stream() << Indentation() << QString("Right: {") << NewLine();
    PushIndentation();
    PrettyPrintNode(binaryExpression->rightExpression());
    PopIndentation();
    stream() << Indentation() << QString("}") << NewLine();

    PopIndentation();
    stream() << Indentation() << QString("}") << NewLine();
}

void ParseTreePrinter::PrettyPrintMemberAccessExpression(MemberAccessExpression* memberAccess)
{
    stream() << Indentation() << StringifyNodeKind(memberAccess->kind()) << QString(": {") << NewLine();
    PushIndentation();

    PrettyPrintNode(memberAccess->expression());

    PopIndentation();
    stream() << Indentation() << QString("}") << NewLine();
}

void ParseTreePrinter::PrettyPrintError(Error* error)
{
    stream() << Indentation() << QString("Error!!") << NewLine();
}
