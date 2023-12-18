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
        case NodeKind::EnumMemberDefinitionStatement:
            return QString("EnumMemberDefinitionStatement");
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

        case NodeKind::TypeNode:
            return QString("TypeNode");
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
        default:
            TODO("String for NodeKind value was not defined yet");
    }
}
