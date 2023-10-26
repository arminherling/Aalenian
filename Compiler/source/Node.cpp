#include "Node.h"

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
        case NodeKind::ReturnStatement:
            return QString("ReturnStatement");
        case NodeKind::Discard:
            return QString("Discard");
        case NodeKind::Parameters:
            return QString("Parameters");
        case NodeKind::Arguments:
            return QString("Arguments");
        case NodeKind::Block:
            return QString("Block");
        case NodeKind::FunctionCall:
            return QString("FunctionCall");
        case NodeKind::Name:
            return QString("Name");
        case NodeKind::Number:
            return QString("Number");
        default:
            assert(!"String for TokenKind value was not defined yet");
            return QString();
    }
}

Node::Node(NodeKind kind)
    : m_kind{ kind }
{
}

Statement::Statement(NodeKind kind)
    : Node(kind)
{
}

Expression::Expression(NodeKind kind)
    : Node(kind)
{
}

Discard::Discard(const Token& token)
    : Expression(NodeKind::Discard)
{
}

Name::Name(const Token& token)
    : Expression(NodeKind::Name)
    , m_token{ token }
{
}

Parameters::Parameters(
    const Token& openParenthesis,
    const Token& closeParenthesis)
    : Node(NodeKind::Parameters)
    , m_openParenthesis{ openParenthesis }
    , m_closeParenthesis{ closeParenthesis }
{
}

Arguments::Arguments(
    const Token& openParenthesis,
    const Token& closeParenthesis)
    : Node(NodeKind::Arguments)
    , m_openParenthesis{ openParenthesis }
    , m_closeParenthesis{ closeParenthesis }
{
}

Block::Block(
    const Token& openBracket,
    const QList<Statement*>& statements,
    const Token& closeBracket)
    : Node(NodeKind::Block)
    , m_openBracket{ openBracket }
    , m_statements{ statements }
    , m_closeBracket{ closeBracket }
{
}

FunctionCall::FunctionCall(const Token& nameToken, Arguments* arguments)
    : Expression(NodeKind::FunctionCall)
    , m_nameToken{ nameToken }
    , m_arguments{ arguments }
{
}

Number::Number(const Token& token)
    : Expression(NodeKind::Number)
    , m_token{ token }
{
}

AssignmentStatement::AssignmentStatement(Expression* leftExpression, const Token& equalsToken, Expression* rightExpression)
    : Statement(NodeKind::AssignmentStatement)
    , m_leftExpression{ leftExpression }
    , m_equalsToken{ equalsToken }
    , m_rightExpression{ rightExpression }
{
}

ExpressionStatement::ExpressionStatement(Expression* expression)
    : Statement(NodeKind::ExpressionStatement)
    , m_expression{ expression }
{
}

ReturnStatement::ReturnStatement(
    const Token& returnKeyword,
    Expression* expression)
    : Statement(NodeKind::ReturnStatement)
    , m_returnKeyword{ returnKeyword }
    , m_expression{ expression }
{
}

FunctionDefinitionStatement::FunctionDefinitionStatement(
    const Token& keyword,
    const Token& name,
    Parameters* parameters,
    Block* body)
    : Statement(NodeKind::FunctionDefinitionStatement)
    , m_keyword{ keyword }
    , m_name{ name }
    , m_parameters{ parameters }
    , m_body{ body }
{
}

TypeDefinitionStatement::TypeDefinitionStatement(
    const Token& keyword,
    const Token& name,
    Block* body)
    : Statement(NodeKind::TypeDefinitionStatement)
    , m_keyword{ keyword }
    , m_name{ name }
    , m_body{ body }
{
}

Error::Error(const Token& token)
    : Expression(NodeKind::Error)
    , m_token{ token }
{
}
