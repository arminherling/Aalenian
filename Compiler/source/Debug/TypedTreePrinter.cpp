#include <Debug/TypedTreePrinter.h>

TypedTreePrinter::TypedTreePrinter(
    TypedTree& typedTree,
    const TypeDatabase& typeDatabase,
    i32 indentation)
    : BasePrinter(indentation)
    , m_typedTree{ typedTree }
    , m_typeDatabase{ typeDatabase }
{
}

QString TypedTreePrinter::PrettyPrint()
{
    for (const auto& globalStatement : m_typedTree.GlobalStatements())
    {
        PrettyPrintNode(globalStatement);
    }

    return toUtf8();
}

void TypedTreePrinter::PrettyPrintNode(TypedNode* node)
{
    switch (node->kind())
    {
        case NodeKind::TypedAssignmentStatement:
        {
            PrettyPrintTypedAssignmentStatement((TypedAssignmentStatement*)node);
            break;
        }
        case NodeKind::TypedFunctionCallExpression:
        {
            PrettyPrintTypedFunctionCallExpression((TypedFunctionCallExpression*)node);
            break;
        }
        case NodeKind::TypedGlobalValue:
        {
            PrettyPrintTypedGlobalValue((TypedGlobalValue*)node);
            break;
        }
        case NodeKind::I32Literal:
        {
            PrettyPrintI32Literal((I32Literal*)node);
            break;
        }
        default:
            stream() << Indentation() << QString("Missing NodeKind!!") << NewLine();
            break;
    }
}

void TypedTreePrinter::PrettyPrintTypedAssignmentStatement(TypedAssignmentStatement* statement)
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

    stream() << Indentation() << PrettyPrintType(statement->type()) << NewLine();

    PopIndentation();
    stream() << Indentation() << QString("}") << NewLine();
}

void TypedTreePrinter::PrettyPrintTypedGlobalValue(TypedGlobalValue* value)
{
    stream() << Indentation() << StringifyNodeKind(value->kind()) << QString(": {") << NewLine();
    PushIndentation();

    stream() << Indentation() << QString("Name: ") << value->name() << NewLine();
    stream() << Indentation() << PrettyPrintType(value->type()) << NewLine();

    PopIndentation();
    stream() << Indentation() << QString("}") << NewLine();
}

void TypedTreePrinter::PrettyPrintTypedFunctionCallExpression(TypedFunctionCallExpression* functionCall)
{

    //auto nameToken = functionCall->name();
    //auto nameLexeme = m_parseTree.Tokens().GetLexeme(nameToken);
    stream() << Indentation() << StringifyNodeKind(functionCall->kind()) << QString(": {") << NewLine();

    PushIndentation();

    stream() << Indentation() << QString("Name: ") << functionCall->name() << NewLine();
    PrettyPrintTypedArgumentsNode(/*functionCall->arguments()*/); // TODO
    stream() << Indentation() << PrettyPrintType(functionCall->type()) << NewLine();

    //stream() << Indentation() << StringifyNodeKind(NodeKind::TypedNameExpression) << QString(": %1").arg(nameLexeme) << NewLine();
    //PrettyPrintArgumentsNode(functionCall->arguments());
    PopIndentation();
    stream() << Indentation() << QString("}") << NewLine();


}

void TypedTreePrinter::PrettyPrintI32Literal(I32Literal* literal)
{
    stream() << Indentation() << StringifyNodeKind(literal->kind()) << QString(": {") << NewLine();
    PushIndentation();

    stream() << Indentation() << QString("Value: ") << literal->value() <<  NewLine();
    stream() << Indentation() << PrettyPrintType(literal->type()) << NewLine();

    PopIndentation();
    stream() << Indentation() << QString("}") << NewLine();
}

void TypedTreePrinter::PrettyPrintTypedArgumentsNode()
{
    // TODO rewrite whole method once we type check the arguments
    stream() << Indentation() << StringifyNodeKind(NodeKind::ArgumentsNode) << QString("(0): {") << NewLine();
    PushIndentation();
    PopIndentation();
    stream() << Indentation() << QString("}") << NewLine();
}

QString TypedTreePrinter::PrettyPrintType(Type type)
{
    auto definition = m_typeDatabase.getTypeDefinition(type);
    return QString("Type: %1").arg(definition.name());
}
