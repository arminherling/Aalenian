#include "TypeChecker.h"

#include <Semantic/Discard.h>
#include <Semantic/I32Literal.h>
#include <Semantic/U8Literal.h>
#include <Semantic/TypedAssignmentStatement.h>
#include <Semantic/TypedEnumDefinitionStatement.h>
#include <Semantic/TypedEnumFieldAccessExpression.h>
#include <Semantic/TypedFunctionCallExpression.h>
#include <Semantic/TypedGlobalValue.h>

TypeChecker::TypeChecker(
    const ParseTree& parseTree, 
    const TypeCheckerOptions& options, 
    Environment& environment, 
    TypeDatabase& typeDatabase, 
    DiagnosticsBag& diagnostics)
    : m_parseTree{ parseTree }
    , m_options{ options }
    , m_environment{ environment }
    , m_typeDatabase{ typeDatabase }
    , m_diagnostics{ diagnostics }
{
}

TypedTree TypeChecker::TypeCheck()
{
    QList<TypedStatement*> globalStatements;

    for (const auto& globalStatement : m_parseTree.GlobalStatements())
    {
        globalStatements.append(TypeCheckStatement(globalStatement));
    }

    return TypedTree(m_parseTree.Tokens(), globalStatements);
}

TypedTree TypeCheck(
    const ParseTree& parseTree, 
    const TypeCheckerOptions& options, 
    Environment& environment, 
    TypeDatabase& typeDatabase, 
    DiagnosticsBag& diagnostics) noexcept
{
    TypeChecker typeChecker{ parseTree, options, environment, typeDatabase, diagnostics };
    return typeChecker.TypeCheck();
}

TypedStatement* TypeChecker::TypeCheckStatement(Statement* statement)
{
    switch (statement->kind())
    {
        case NodeKind::AssignmentStatement:
        {
            return TypeCheckAssignmentStatement((AssignmentStatement*)statement);
        }
        case NodeKind::EnumDefinitionStatement:
        {
            return TypeCheckEnumDefinitionStatement((EnumDefinitionStatement*)statement);
        }
        default:
        {
            TODO("Missing Statement!!");
        }
    }
}

TypedExpression* TypeChecker::TypeCheckExpression(Expression* expression)
{
    switch (expression->kind())
    {
        case NodeKind::BinaryExpression:
        {
            return TypeCheckBinaryExpressionExpression((BinaryExpression*)expression);
        }
        case NodeKind::FunctionCallExpression:
        {
            return TypeCheckFunctionCallExpression((FunctionCallExpression*)expression);
        }
        case NodeKind::NameExpression:
        {
            return TypeCheckNameExpression((NameExpression*)expression);
        }
        case NodeKind::DiscardLiteral:
        {
            return TypeCheckDiscardLiteral((DiscardLiteral*)expression);
        }
        case NodeKind::NumberLiteral:
        {
            return TypeCheckNumberLiteral((NumberLiteral*)expression);
        }
        default:
        {
            TODO("Missing Expression!!");
        }
    }
}

TypedStatement* TypeChecker::TypeCheckAssignmentStatement(AssignmentStatement* statement)
{
    auto left = TypeCheckExpression(statement->leftExpression());
    auto right = TypeCheckExpression(statement->rightExpression());

    auto inferedType = Type::Undefined();
    if (left->type() == Type::Undefined() && right != nullptr)
    {
        inferedType = inferType(right);
        left->setType(inferedType);
    }

    if (left->kind() == NodeKind::TypedGlobalValue)
    {
        auto globalValue = ((TypedGlobalValue*)left);
        m_environment.addBinding(globalValue->name(), globalValue->type());
    }

    return new TypedAssignmentStatement(left, right, statement, inferedType);
}

TypedStatement* TypeChecker::TypeCheckEnumDefinitionStatement(EnumDefinitionStatement* statement)
{
    auto optionalBaseTypeName = statement->baseType();
    auto baseType = Type::Undefined();
    if (optionalBaseTypeName.has_value())
    {
        auto typeName = optionalBaseTypeName.value().name();
        auto identifier = typeName->identifier();
        auto lexeme = m_parseTree.Tokens().GetLexeme(identifier);
        baseType = m_typeDatabase.getTypeByName(lexeme);
    }
    else
    {
        baseType = m_options.defaultEnumBaseType;
    }

    if (baseType == Type::Undefined())
    {
        // TODO We need an error node and need to print diagnostics about unknown enum base type
    }


    auto nameToken = statement->name();
    auto enumName = m_parseTree.Tokens().GetLexeme(nameToken);
    auto enumType = m_typeDatabase.createType(enumName, TypeKind::Enum);
    auto enumFields = TypeCheckEnumFieldDefinitionNodes(enumType, baseType, statement->fieldDefinitions());

    return new TypedEnumDefinitionStatement(enumName, enumType, baseType, enumFields, statement);
}

QList<TypedEnumFieldDefinitionNode*> TypeChecker::TypeCheckEnumFieldDefinitionNodes(Type enumType, Type baseType, const QList<EnumFieldDefinitionStatement*> fieldDefinitions)
{
    auto& enumTypeDefinition = m_typeDatabase.getTypeDefinition(enumType);

    QList<TypedEnumFieldDefinitionNode*> enumFields;
    int nextValue = 0;
    for (const auto definition : fieldDefinitions)
    {
        auto nameToken = definition->name()->identifier();
        auto name = m_parseTree.Tokens().GetLexeme(nameToken);
        
        if (definition->value().has_value())
        {
            auto numberLiteral = definition->value().value();
            auto numberToken = numberLiteral->token();
            auto valueLexeme = m_parseTree.Tokens().GetLexeme(numberToken);

            auto [typedLiteral, value] = ConvertValueToTypedLiteral(valueLexeme, baseType, definition);
            if (typedLiteral != nullptr)
            {
                nextValue = value + 1;
                enumFields.append(new TypedEnumFieldDefinitionNode(name, typedLiteral));
                enumTypeDefinition.addField(enumType, name, typedLiteral);
            }
        }
        else
        {
            auto [typedLiteral, value] = ConvertValueToTypedLiteral(nextValue++, baseType, definition);
            if (typedLiteral != nullptr)
            {
                enumFields.append(new TypedEnumFieldDefinitionNode(name, typedLiteral));
                enumTypeDefinition.addField(enumType, name, typedLiteral);
            }
        }
    }
    return enumFields;
}

TypedExpression* TypeChecker::TypeCheckBinaryExpressionExpression(BinaryExpression* binaryExpression)
{
    switch (binaryExpression->binaryOperator())
    {
        case BinaryOperatornKind::ScopeAccess:
        {
            auto leftExpression = binaryExpression->leftExpression();
            //TODO disallow other expressions
            assert(leftExpression->kind() == NodeKind::NameExpression);
            auto scopeNameExpression = (NameExpression*)leftExpression;
            auto scopeName = m_parseTree.Tokens().GetLexeme(scopeNameExpression->identifier());
            auto scopeType = m_typeDatabase.getTypeByName(scopeName);
            auto scopeTypeDefinition = m_typeDatabase.getTypeDefinition(scopeType);

            switch (scopeTypeDefinition.kind())
            {
                case TypeKind::Enum:
                {
                    auto rightExpression = binaryExpression->rightExpression();
                    //TODO allow/disallow other expressions
                    assert(rightExpression->kind() == NodeKind::NameExpression);
                    auto fieldNameExpression = (NameExpression*)rightExpression;
                    auto fieldName = m_parseTree.Tokens().GetLexeme(fieldNameExpression->identifier());
                    auto enumField = scopeTypeDefinition.getFieldByName(fieldName);
                    return new TypedEnumFieldAccessExpression(scopeType, enumField, binaryExpression);
                }
            }
        }
        default:
        {
            TODO("Missing Expression!!");
        }
    }

    return nullptr;
}

TypedExpression* TypeChecker::TypeCheckNameExpression(NameExpression* expression)
{
    auto identifier = expression->identifier();
    auto lexeme = m_parseTree.Tokens().GetLexeme(identifier);
    auto type = m_environment.tryGetBinding(lexeme);
    return new TypedGlobalValue(lexeme, expression, type);
}

TypedExpression* TypeChecker::TypeCheckDiscardLiteral(DiscardLiteral* literal)
{
    return new Discard(literal);
}

TypedExpression* TypeChecker::TypeCheckNumberLiteral(NumberLiteral* literal)
{
    auto numberType = Type::Undefined();
    if (literal->type().has_value())
    {
        auto typeToken = literal->type().value();
        auto identifierToken = typeToken.name()->identifier();
        auto typeName = m_parseTree.Tokens().GetLexeme(identifierToken);
        
        numberType = m_typeDatabase.getTypeByName(typeName);
    }
    else
    {
        numberType = m_options.defaultIntegerType;
    }

    auto numberToken = literal->token();
    auto valueLexeme = m_parseTree.Tokens().GetLexeme(numberToken);

    auto [typedLiteral, value] = ConvertValueToTypedLiteral(valueLexeme, numberType, literal);
    if (typedLiteral != nullptr)
        return typedLiteral;

    // TODO We need an error node and need to print diagnostics about unknown number type
    return nullptr;
}

TypedExpression* TypeChecker::TypeCheckFunctionCallExpression(FunctionCallExpression* functionCallExpression)
{
    auto name = functionCallExpression->name();
    auto lexeme = m_parseTree.Tokens().GetLexeme(name);
    auto type = m_environment.tryGetBinding(lexeme);
    // TODO type check parameters and find the correct function call
    // TODO check if function was defined before and what type it returns, assume undefined for now
    // TODO print diagnostic if the function wasnt defined before
    return new TypedFunctionCallExpression(lexeme, functionCallExpression, Type::Undefined());
}

Type TypeChecker::inferType(TypedNode* node)
{
    return node->type();
}

std::tuple<TypedExpression*, i32> TypeChecker::ConvertValueToTypedLiteral(QStringView valueLexeme, Type type, Node* source)
{
    if (type == Type::U8())
    {
        bool ok;
        auto value = valueLexeme.toInt(&ok);
        assert(ok);
        
        // TODO add error for values outside of the u8 range
        assert(value >= 0);
        assert(value <= UINT8_MAX);

        return { new U8Literal((u8)value, source, type), value };
    }
    else if (type == Type::I32())
    {
        bool ok;
        auto value = valueLexeme.toInt(&ok);
        assert(ok);

        // TODO add error for values outside of the i32 range

        return { new I32Literal(value, source, type), value };
    }

    return { nullptr, 0 };
}

std::tuple<TypedExpression*, i32> TypeChecker::ConvertValueToTypedLiteral(i32 value, Type type, Node* source)
{
    if (type == Type::U8())
    {
        // TODO add error for values outside of the u8 range
        assert(value >= 0);
        assert(value <= UINT8_MAX);

        return { new U8Literal((u8)value, source, type), value };
    }
    else if (type == Type::I32())
    {
        return { new I32Literal(value, source, type), value };
    }

    return { nullptr, 0 };

}
