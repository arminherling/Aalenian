#include "NodeKind.h"

QString StringifyNodeKind(NodeKind kind)
{
    switch (kind)
    {
        case NodeKind::Unknown:
            return QString("Unknown");
        case NodeKind::Error:
            return QString("Error");

        case NodeKind::AssignmentStatement:
            return QString("AssignmentStatement");
        case NodeKind::ExpressionStatement:
            return QString("ExpressionStatement");
        case NodeKind::FunctionDefinitionStatement:
            return QString("FunctionDefinitionStatement");
        case NodeKind::EnumDefinitionStatement:
            return QString("EnumDefinitionStatement");
        case NodeKind::EnumFieldDefinitionStatement:
            return QString("EnumFieldDefinitionStatement");
        case NodeKind::TypeDefinitionStatement:
            return QString("TypeDefinitionStatement");
        case NodeKind::FieldDeclarationStatement:
            return QString("FieldDeclarationStatement");
        case NodeKind::MethodDefinitionStatement:
            return QString("MethodDefinitionStatement");
        case NodeKind::IfStatement:
            return QString("IfStatement");
        case NodeKind::WhileStatement:
            return QString("WhileStatement");
        case NodeKind::ReturnStatement:
            return QString("ReturnStatement");

        case NodeKind::UnaryExpression:
            return QString("UnaryExpression");
        case NodeKind::BinaryExpression:
            return QString("BinaryExpression");
        case NodeKind::FunctionCallExpression:
            return QString("FunctionCallExpression");
        case NodeKind::NameExpression:
            return QString("NameExpression");
        case NodeKind::GroupingExpression:
            return QString("GroupingExpression");
        case NodeKind::ScopeAccessExpression:
            return QString("ScopeAccessExpression");
        case NodeKind::MemberAccessExpression:
            return QString("MemberAccessExpression");

        case NodeKind::DiscardLiteral:
            return QString("DiscardLiteral");
        case NodeKind::BoolLiteral:
            return QString("BoolLiteral");
        case NodeKind::NumberLiteral:
            return QString("NumberLiteral");

        case NodeKind::TypeName:
            return QString("TypeName");
        case NodeKind::ArgumentNode:
            return QString("ArgumentNode");
        case NodeKind::ArgumentsNode:
            return QString("ArgumentsNode");
        case NodeKind::ParameterNode:
            return QString("ParameterNode");
        case NodeKind::ParametersNode:
            return QString("ParametersNode");
        case NodeKind::BlockNode:
            return QString("BlockNode");

        case NodeKind::TypedAssignmentStatement:
            return QString("TypedAssignmentStatement");
        case NodeKind::TypedExpressionStatement:
            return QString("TypedExpressionStatement");
        case NodeKind::TypedEnumDefinitionStatement:
            return QString("TypedEnumDefinitionStatement");
        case NodeKind::TypedFieldDefinitionNode:
            return QString("TypedFieldDefinitionNode");
        case NodeKind::TypedTypeDefinitionStatement:
            return QString("TypedTypeDefinitionStatement");
        case NodeKind::TypedFunctionDefinitionStatement:
            return QString("TypedFunctionDefinitionStatement");
        case NodeKind::TypedReturnStatement:
            return QString("TypedReturnStatement");

        case NodeKind::TypedNegationExpression:
            return QString("TypedNegationExpression");
        case NodeKind::TypedEnumFieldAccessExpression:
            return QString("TypedEnumFieldAccessExpression");
        case NodeKind::TypedAdditionExpression:
            return QString("TypedAdditionExpression");
        case NodeKind::TypedSubtractionExpression:
            return QString("TypedSubtractionExpression");
        case NodeKind::TypedMultiplicationExpression:
            return QString("TypedMultiplicationExpression");
        case NodeKind::TypedDivisionExpression:
            return QString("TypedDivisionExpression");
        case NodeKind::TypedFunctionCallExpression:
            return QString("TypedFunctionCallExpression");

        case NodeKind::TypedConstant:
            return QString("TypedConstant");
        case NodeKind::TypedVariable:
            return QString("TypedVariable");
        case NodeKind::Discard:
            return QString("Discard");
        case NodeKind::BoolValue:
            return QString("BoolValue");
        case NodeKind::U8Literal:
            return QString("U8Literal");
        case NodeKind::I32Literal:
            return QString("I32Literal");

        case NodeKind::Parameter:
            return QString("Parameter");

        default:
            TODO("String for NodeKind value was not defined yet");
    }
}
