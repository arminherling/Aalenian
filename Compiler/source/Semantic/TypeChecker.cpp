#include "TypeChecker.h"

#include <Semantic/Discard.h>
#include <Semantic/I32Literal.h>
#include <Semantic/U8Literal.h>
#include <Semantic/TypedAssignmentStatement.h>
#include <Semantic/TypedEnumDefinitionStatement.h>
#include <Semantic/TypedEnumFieldAccessExpression.h>
#include <Semantic/TypedFunctionCallExpression.h>
#include <Semantic/TypedGlobalValue.h>
#include <Semantic/TypedNegationExpression.h>
#include <Semantic/TypedTypeDefinitionStatement.h>
#include <Syntax/FieldDeclarationStatement.h>

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

TypedTree TypeChecker::typeCheck()
{
    QList<TypedStatement*> globalStatements;

    for (const auto& globalStatement : m_parseTree.globalStatements())
    {
        globalStatements.append(typeCheckStatement(globalStatement));
    }

    return TypedTree(m_parseTree.tokens(), globalStatements);
}

TypedTree TypeCheck(
    const ParseTree& parseTree, 
    const TypeCheckerOptions& options, 
    Environment& environment, 
    TypeDatabase& typeDatabase, 
    DiagnosticsBag& diagnostics) noexcept
{
    TypeChecker typeChecker{ parseTree, options, environment, typeDatabase, diagnostics };
    return typeChecker.typeCheck();
}

TypedStatement* TypeChecker::typeCheckStatement(Statement* statement)
{
    switch (statement->kind())
    {
        case NodeKind::AssignmentStatement:
        {
            return typeCheckAssignmentStatement((AssignmentStatement*)statement);
        }
        case NodeKind::EnumDefinitionStatement:
        {
            return typeCheckEnumDefinitionStatement((EnumDefinitionStatement*)statement);
        }
        case NodeKind::TypeDefinitionStatement:
        {
            return typeCheckTypeDefinitionStatement((TypeDefinitionStatement*)statement);
        }
        default:
        {
            TODO("Missing Statement!!");
        }
    }
}

TypedExpression* TypeChecker::typeCheckExpression(Expression* expression)
{
    switch (expression->kind())
    {
        case NodeKind::UnaryExpression:
        {
            return typeCheckUnaryExpressionExpression((UnaryExpression*)expression);
        }
        case NodeKind::BinaryExpression:
        {
            return typeCheckBinaryExpressionExpression((BinaryExpression*)expression);
        }
        case NodeKind::FunctionCallExpression:
        {
            return typeCheckFunctionCallExpression((FunctionCallExpression*)expression);
        }
        case NodeKind::NameExpression:
        {
            return typeCheckNameExpression((NameExpression*)expression);
        }
        case NodeKind::DiscardLiteral:
        {
            return typeCheckDiscardLiteral((DiscardLiteral*)expression);
        }
        case NodeKind::NumberLiteral:
        {
            return typeCheckNumberLiteral((NumberLiteral*)expression);
        }
        default:
        {
            TODO("Missing Expression!!");
        }
    }
}

TypedStatement* TypeChecker::typeCheckAssignmentStatement(AssignmentStatement* statement)
{
    auto left = typeCheckExpression(statement->leftExpression());
    auto right = typeCheckExpression(statement->rightExpression());

    auto inferedType = inferType(right);
    
    if (left->type() == Type::Undefined())
    {
        left->setType(inferedType);

        auto globalValue = ((TypedGlobalValue*)left);
        m_environment.addBinding(globalValue->name(), globalValue->type());
    }

    auto leftType = left->type();
    if (leftType != Type::Discard()
        && leftType != inferedType)
    {
        TODO("error type mismatch!!");
    }

    return new TypedAssignmentStatement(left, right, statement, inferedType);
}

TypedStatement* TypeChecker::typeCheckEnumDefinitionStatement(EnumDefinitionStatement* statement)
{
    auto optionalBaseTypeName = statement->baseType();
    auto baseType = Type::Undefined();
    if (optionalBaseTypeName.has_value())
    {
        auto typeName = optionalBaseTypeName.value().name();
        auto identifier = typeName->identifier();
        auto lexeme = m_parseTree.tokens().getLexeme(identifier);
        baseType = m_typeDatabase.getTypeByName(lexeme);
    }
    else
    {
        baseType = m_options.defaultEnumBaseType;
    }

    if (baseType == Type::Undefined())
    {
        TODO("We need an error node and need to print diagnostics about unknown enum base type");
    }

    auto nameToken = statement->name();
    auto enumName = m_parseTree.tokens().getLexeme(nameToken);
    // TODO check if there is already a type with the name
    auto newType = m_typeDatabase.createType(enumName, TypeKind::Enum);
    auto enumFields = typeCheckEnumFieldDefinitionNodes(newType, baseType, statement->fieldDefinitions());

    return new TypedEnumDefinitionStatement(enumName, newType, baseType, enumFields, statement);
}

TypedStatement* TypeChecker::typeCheckTypeDefinitionStatement(TypeDefinitionStatement* statement)
{
    auto nameToken = statement->name();
    auto typeName = m_parseTree.tokens().getLexeme(nameToken);
    // TODO check if there is already a type with the name
    auto newType = m_typeDatabase.createType(typeName, TypeKind::Type);
    auto typeFields = typeCheckTypeFieldDefinitionNodes(newType, statement->body());
    // TODO typecheck methods

    return new TypedTypeDefinitionStatement(typeName, newType, typeFields, statement);
}

QList<TypedFieldDefinitionNode*> TypeChecker::typeCheckEnumFieldDefinitionNodes(
    Type newType, 
    Type baseType, 
    const QList<EnumFieldDefinitionStatement*>& fieldDefinitions)
{
    auto& enumTypeDefinition = m_typeDatabase.getTypeDefinition(newType);

    QList<TypedFieldDefinitionNode*> enumFields;
    int nextValue = 0;
    for (const auto definition : fieldDefinitions)
    {
        auto nameToken = definition->name()->identifier();
        auto name = m_parseTree.tokens().getLexeme(nameToken);
        
        if (definition->value().has_value())
        {
            auto numberLiteral = definition->value().value();
            auto numberToken = numberLiteral->token();
            auto valueLexeme = m_parseTree.tokens().getLexeme(numberToken);

            auto [typedLiteral, value] = convertValueToTypedLiteral(valueLexeme, baseType, definition);
            if (typedLiteral != nullptr)
            {
                nextValue = value + 1;
                enumFields.append(new TypedFieldDefinitionNode(name, baseType, typedLiteral));
                enumTypeDefinition.addField(newType, name, typedLiteral);
            }
        }
        else
        {
            auto [typedLiteral, value] = convertValueToTypedLiteral(nextValue++, baseType, definition);
            if (typedLiteral != nullptr)
            {
                enumFields.append(new TypedFieldDefinitionNode(name, baseType, typedLiteral));
                enumTypeDefinition.addField(newType, name, typedLiteral);
            }
        }
    }
    return enumFields;
}

QList<TypedFieldDefinitionNode*> TypeChecker::typeCheckTypeFieldDefinitionNodes(Type newType, BlockNode* body)
{
    auto& typeDefinition = m_typeDatabase.getTypeDefinition(newType);

    QList<TypedFieldDefinitionNode*> typeFields;

    for (const auto statement : body->statements())
    {
        if (statement->kind() != NodeKind::FieldDeclarationStatement)
            continue;

        auto fieldDeclaration = (FieldDeclarationStatement*)statement;
        auto nameToken = fieldDeclaration->name()->identifier();
        auto name = m_parseTree.tokens().getLexeme(nameToken);
        
        auto type = Type::Undefined();
        if (fieldDeclaration->type().has_value())
        {
            auto fieldTypeName = fieldDeclaration->type().value();
            type = convertTypeNameToType(fieldTypeName);
        }

        TypedExpression* expression = nullptr;
        if (fieldDeclaration->expression().has_value())
        {
            auto fieldExpression = fieldDeclaration->expression().value();
            expression = typeCheckExpression(fieldExpression);

            if (type == Type::Undefined())
            {
                type = expression->type();
            }
            else if (type != expression->type())
            {
                TODO("error type mismatch!!");
            }
        }

        if (type == Type::Undefined())
        {
            // NOTE We might want to infer the types in the constructor in the future
            TODO("error missing type for field!!");
        }

        typeFields.append(new TypedFieldDefinitionNode(name, type, expression));
        typeDefinition.addField(newType, name, expression);
    }

    return typeFields;
}

TypedExpression* TypeChecker::typeCheckUnaryExpressionExpression(UnaryExpression* unaryExpression)
{
    switch (unaryExpression->unaryOperator())
    {
        case UnaryOperatornKind::Negation:
        {
            auto expression = unaryExpression->expression();
            auto typedExpression = typeCheckExpression(expression);
            //TODO if possible check that values are still in range after negation
            auto type = typedExpression->type();
            return new TypedNegationExpression(type, typedExpression, unaryExpression);
        }
        default:
        {
            TODO("Missing UnaryOperatornKind!!");
        }
    }

    return nullptr;
}

TypedExpression* TypeChecker::typeCheckBinaryExpressionExpression(BinaryExpression* binaryExpression)
{
    switch (binaryExpression->binaryOperator())
    {
        case BinaryOperatornKind::ScopeAccess:
        {
            auto leftExpression = binaryExpression->leftExpression();
            //TODO disallow other expressions
            assert(leftExpression->kind() == NodeKind::NameExpression);
            auto scopeNameExpression = (NameExpression*)leftExpression;
            auto scopeName = m_parseTree.tokens().getLexeme(scopeNameExpression->identifier());
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
                    auto fieldName = m_parseTree.tokens().getLexeme(fieldNameExpression->identifier());
                    auto enumField = scopeTypeDefinition.getFieldByName(fieldName);
                    return new TypedEnumFieldAccessExpression(scopeType, enumField, binaryExpression);
                }
            }
        }
        default:
        {
            TODO("Missing BinaryOperatornKind!!");
        }
    }

    return nullptr;
}

TypedExpression* TypeChecker::typeCheckNameExpression(NameExpression* expression)
{
    auto identifier = expression->identifier();
    auto lexeme = m_parseTree.tokens().getLexeme(identifier);
    auto type = m_environment.tryGetBinding(lexeme);
    return new TypedGlobalValue(lexeme, expression, type);
}

TypedExpression* TypeChecker::typeCheckDiscardLiteral(DiscardLiteral* literal)
{
    return new Discard(literal);
}

TypedExpression* TypeChecker::typeCheckNumberLiteral(NumberLiteral* literal)
{
    auto numberType = Type::Undefined();
    if (literal->type().has_value())
    {
        auto typeToken = literal->type().value();
        auto identifierToken = typeToken.name()->identifier();
        auto typeName = m_parseTree.tokens().getLexeme(identifierToken);
        
        numberType = m_typeDatabase.getTypeByName(typeName);
    }
    else
    {
        numberType = m_options.defaultIntegerType;
    }

    auto numberToken = literal->token();
    auto valueLexeme = m_parseTree.tokens().getLexeme(numberToken);

    auto [typedLiteral, value] = convertValueToTypedLiteral(valueLexeme, numberType, literal);
    if (typedLiteral != nullptr)
        return typedLiteral;

    // TODO We need an error node and need to print diagnostics about unknown number type
    return nullptr;
}

TypedExpression* TypeChecker::typeCheckFunctionCallExpression(FunctionCallExpression* functionCallExpression)
{
    auto name = functionCallExpression->name();
    auto lexeme = m_parseTree.tokens().getLexeme(name);
    auto type = m_environment.tryGetBinding(lexeme);
    // TODO type check parameters and find the correct function call
    // TODO check if function was defined before and what type it returns, assume undefined for now
    // TODO print diagnostic if the function wasnt defined before
    return new TypedFunctionCallExpression(lexeme, functionCallExpression, Type::Undefined());
}

Type TypeChecker::inferType(TypedNode* node)
{
    if (node == nullptr)
        return Type::Undefined();

    return node->type();
}

Type TypeChecker::convertTypeNameToType(const TypeName& typeName)
{
    auto nameToken = typeName.name()->identifier();
    auto nameLexeme = m_parseTree.tokens().getLexeme(nameToken);

    // TODO handle ref
    // returns Type::Undefined() if the name wasnt found
    return m_typeDatabase.getTypeByName(nameLexeme);
}

std::tuple<TypedExpression*, i32> TypeChecker::convertValueToTypedLiteral(QStringView valueLexeme, Type type, Node* source)
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

std::tuple<TypedExpression*, i32> TypeChecker::convertValueToTypedLiteral(i32 value, Type type, Node* source)
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
