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
        case NodeKind::TypeDefinitionStatement:
            return QString("TypeDefinitionStatement");
        case NodeKind::EnumDefinitionStatement:
            return QString("EnumDefinitionStatement");
        case NodeKind::EnumMemberDefinitionStatement:
            return QString("EnumMember");
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
        case NodeKind::DiscardLiteral:
            return QString("Discard");
        case NodeKind::ArgumentNode:
            return QString("Argument");
        case NodeKind::ArgumentsNode:
            return QString("Arguments");
        case NodeKind::ParameterNode:
            return QString("Parameter");
        case NodeKind::ParametersNode:
            return QString("Parameters");
        case NodeKind::BlockNode:
            return QString("Block");
        case NodeKind::FunctionCallExpression:
            return QString("FunctionCall");
        case NodeKind::BoolLiteral:
            return QString("Bool");
        case NodeKind::NameExpression:
            return QString("Name");
        case NodeKind::NumberLiteral:
            return QString("Number");
        case NodeKind::GroupingExpression:
            return QString("Grouping");
        case NodeKind::UnaryExpression:
            return QString("UnaryExpression");
        case NodeKind::BinaryExpression:
            return QString("BinaryExpression");
        case NodeKind::MemberAccessExpression:
            return QString("MemberAccess");
        default:
            TODO("String for NodeKind value was not defined yet");
    }
}
