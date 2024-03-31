#include "TypeChecker.h"

#include <Semantic/Discard.h>
#include <Semantic/I32Literal.h>
#include <Semantic/TypedAssignmentStatement.h>
#include <Semantic/TypedEnumDefinitionStatement.h>
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
        case NodeKind::FunctionCallExpression:
        {
            return TypeCheckFunctionCallExpression((FunctionCallExpression*)expression);
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

    auto inferedType = inferType(right);
    
    if (left->type() == Type::Undefined())
    {
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
        baseType = m_typeDatabase.getBuiltinTypeByName(lexeme);

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
    auto type = m_typeDatabase.createType(enumName);

    return new TypedEnumDefinitionStatement(enumName, type, baseType, statement);
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
        
        numberType = m_typeDatabase.getBuiltinTypeByName(typeName);
    }
    else
    {
        numberType = m_options.defaultIntegerType;
    }

    auto numberToken = literal->token();
    auto valueLexeme = m_parseTree.Tokens().GetLexeme(numberToken);

    if (numberType == Type::I32())
    {
        bool ok;
        auto value = valueLexeme.toInt(&ok);

        assert(ok);

        return new I32Literal(value, literal, numberType);
    }

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
