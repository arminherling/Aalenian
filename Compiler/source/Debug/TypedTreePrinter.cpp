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
    for (const auto& globalStatement : m_typedTree.globalStatements())
    {
        PrettyPrintNode(globalStatement);
    }

    return toUtf8();
}

void TypedTreePrinter::PrettyPrintNode(TypedNode* node)
{
    if (node == nullptr)
    {
        stream() << Indentation() << QString("TypedNode was null!!") << NewLine();
        return;
    }

    switch (node->kind())
    {
        case NodeKind::TypedAssignmentStatement:
        {
            PrettyPrintTypedAssignmentStatement((TypedAssignmentStatement*)node);
            break;
        }
        case NodeKind::TypedEnumDefinitionStatement:
        {
            PrettyPrintTypedEnumDefinitionStatement((TypedEnumDefinitionStatement*)node);
            break;
        }
        case NodeKind::TypedTypeDefinitionStatement:
        {
            PrettyPrintTypedTypeDefinitionStatement((TypedTypeDefinitionStatement*)node);
            break;
        }
        case NodeKind::TypedNegationExpression:
        {
            PrettyPrintTypedNegationExpression((TypedNegationExpression*)node);
            break;
        }
        case NodeKind::TypedEnumFieldAccessExpression:
        {
            PrettyPrintTypedEnumFieldAccessExpression((TypedEnumFieldAccessExpression*)node);
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
        case NodeKind::Discard:
        {
            PrettyPrintDiscard((Discard*)node);
            break;
        }
        case NodeKind::U8Literal:
        {
            PrettyPrintU8Literal((U8Literal*)node);
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

void TypedTreePrinter::PrettyPrintTypedEnumDefinitionStatement(TypedEnumDefinitionStatement* statement)
{
    stream() << Indentation() << StringifyNodeKind(statement->kind()) << QString(": {") << NewLine();
    PushIndentation();

    stream() << Indentation() << QString("TypeKind: enum") << NewLine();
    stream() << Indentation() << QString("TypeName: ") << statement->name() << NewLine();

    auto baseTypeDefinition = m_typeDatabase.getTypeDefinition(statement->baseType());
    stream() << Indentation() << QString("BaseType: ") << baseTypeDefinition.name() << NewLine();

    auto fields = statement->fields();
    stream() << Indentation() << QString("Fields(%1): {").arg(fields.count()) << NewLine();
    PushIndentation();
    for (const auto& field : fields)
    {
        stream() << Indentation() << StringifyNodeKind(field->kind()) << QString(": {") << NewLine();
        PushIndentation();
        stream() << Indentation() << QString("Name: ") << field->name() << NewLine();
        stream() << Indentation() << QString("Value: ") << PrettyPrintEnumFieldValue(field->value()) << NewLine();
        PopIndentation();
        stream() << Indentation() << QString("}") << NewLine();
    }

    PopIndentation();
    stream() << Indentation() << QString("}") << NewLine();

    PopIndentation();
    stream() << Indentation() << QString("}") << NewLine();
}

void TypedTreePrinter::PrettyPrintTypedTypeDefinitionStatement(TypedTypeDefinitionStatement* statement)
{
    stream() << Indentation() << StringifyNodeKind(statement->kind()) << QString(": {") << NewLine();
    PushIndentation();

    stream() << Indentation() << QString("TypeKind: type") << NewLine();
    stream() << Indentation() << QString("TypeName: ") << statement->name() << NewLine();

    stream() << Indentation() << QString("Fields(%1): {").arg(0) << NewLine();
    PushIndentation();
    PopIndentation();
    stream() << Indentation() << QString("}") << NewLine();

    stream() << Indentation() << QString("Methods(%1): {").arg(0) << NewLine();
    PushIndentation();
    PopIndentation();
    stream() << Indentation() << QString("}") << NewLine();

    PopIndentation();
    stream() << Indentation() << QString("}") << NewLine();
}

void TypedTreePrinter::PrettyPrintTypedNegationExpression(TypedNegationExpression* expression)
{
    stream() << Indentation() << StringifyNodeKind(expression->kind()) << QString(": {") << NewLine();
    PushIndentation();

    stream() << Indentation() << PrettyPrintType(expression->type()) << NewLine();
    stream() << Indentation() << QString("Expression: {") << NewLine();
    PushIndentation();

    PrettyPrintNode(expression->expression());

    PopIndentation();
    stream() << Indentation() << QString("}") << NewLine();

    PopIndentation();
    stream() << Indentation() << QString("}") << NewLine();
}

void TypedTreePrinter::PrettyPrintTypedEnumFieldAccessExpression(TypedEnumFieldAccessExpression* expression)
{
    stream() << Indentation() << StringifyNodeKind(expression->kind()) << QString(": {") << NewLine();
    PushIndentation();

    stream() << Indentation() << PrettyPrintType(expression->type()) << NewLine();
    stream() << Indentation() << QString("Name: ") << expression->fieldName() << NewLine();
    stream() << Indentation() << QString("Value: ") << PrettyPrintEnumFieldValue(expression->field()->value()) << NewLine();

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
    stream() << Indentation() << StringifyNodeKind(functionCall->kind()) << QString(": {") << NewLine();

    PushIndentation();

    stream() << Indentation() << QString("Name: ") << functionCall->name() << NewLine();
    PrettyPrintTypedArgumentsNode(/*functionCall->arguments()*/); // TODO
    stream() << Indentation() << PrettyPrintType(functionCall->type()) << NewLine();

    PopIndentation();
    stream() << Indentation() << QString("}") << NewLine();
}

void TypedTreePrinter::PrettyPrintDiscard(Discard* discard)
{
    stream() << Indentation() << StringifyNodeKind(discard->kind()) << QString(": {") << NewLine();
    PushIndentation();

    stream() << Indentation() << PrettyPrintType(discard->type()) << NewLine();

    PopIndentation();
    stream() << Indentation() << QString("}") << NewLine();
}

void TypedTreePrinter::PrettyPrintU8Literal(U8Literal* literal)
{
    stream() << Indentation() << StringifyNodeKind(literal->kind()) << QString(": {") << NewLine();
    PushIndentation();

    stream() << Indentation() << QString("Value: ") << literal->value() << NewLine();
    stream() << Indentation() << PrettyPrintType(literal->type()) << NewLine();

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

QString TypedTreePrinter::PrettyPrintType(Type type) noexcept
{
    auto definition = m_typeDatabase.getTypeDefinition(type);
    return QString("Type: %1").arg(definition.name());
}

QString TypedTreePrinter::PrettyPrintEnumFieldValue(TypedExpression* exppression) const noexcept
{
    switch (exppression->kind())
    {
        case NodeKind::U8Literal:
        {
            auto u8Literal = (U8Literal*)exppression;
            return QString::number(u8Literal->value());
        }
        case NodeKind::I32Literal:
        {
            auto i32Literal = (I32Literal*)exppression;
            return QString::number(i32Literal->value());
        }
    }

    return QString();
}
