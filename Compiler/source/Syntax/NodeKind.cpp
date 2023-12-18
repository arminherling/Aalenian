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
        case NodeKind::EnumMember:
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
        case NodeKind::Discard:
            return QString("Discard");
        case NodeKind::Argument:
            return QString("Argument");
        case NodeKind::Arguments:
            return QString("Arguments");
        case NodeKind::Parameter:
            return QString("Parameter");
        case NodeKind::Parameters:
            return QString("Parameters");
        case NodeKind::Block:
            return QString("Block");
        case NodeKind::FunctionCall:
            return QString("FunctionCall");
        case NodeKind::Bool:
            return QString("Bool");
        case NodeKind::Name:
            return QString("Name");
        case NodeKind::Number:
            return QString("Number");
        case NodeKind::Grouping:
            return QString("Grouping");
        case NodeKind::UnaryExpression:
            return QString("UnaryExpression");
        case NodeKind::BinaryExpression:
            return QString("BinaryExpression");
        case NodeKind::MemberAccess:
            return QString("MemberAccess");
        default:
            TODO("String for NodeKind value was not defined yet");
    }
}
