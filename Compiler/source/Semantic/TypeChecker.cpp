#include "TypeChecker.h"

#include <Semantic/TypedGlobalValue.h>
#include <Semantic/TypedAssignmentStatement.h>
#include <Semantic/I32Literal.h>

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

TypedExpression* TypeChecker::TypeCheckNameExpression(NameExpression* expression)
{
    auto identifier = expression->identifier();
    auto lexeme = m_parseTree.Tokens().GetLexeme(identifier);
    auto type = m_environment.tryGetBinding(lexeme);
    return new TypedGlobalValue(lexeme, expression, type);
}

TypedExpression* TypeChecker::TypeCheckNumberLiteral(NumberLiteral* literal)
{
    auto numberType = Type::Undefined();
    if (literal->type().has_value())
    {
        auto typeToken = literal->type().value();
        auto identifierToken = typeToken.name()->identifier();
        auto typeName = m_parseTree.Tokens().GetLexeme(identifierToken);
        
        numberType = m_typeDatabase.getBuiltinNumberTypeByName(typeName);
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

    // We need an error node and need to print diagnostics about unknown number type
    return nullptr;
}

Type TypeChecker::inferType(TypedNode* node)
{
    return node->type();
}
