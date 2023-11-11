#include <Syntax/Node.h>

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
        case NodeKind::Grouping:
            return QString("Grouping");
        case NodeKind::UnaryExpression:
            return QString("UnaryExpression");
        case NodeKind::BinaryExpression:
            return QString("BinaryExpression");
        case NodeKind::MemberAccess:
            return QString("MemberAccess");
        default:
            assert(!"String for NodeKind value was not defined yet");
            return QString();
    }
}

COMPILER_API QString StringifyUnaryOperation(TokenKind kind)
{
    switch (kind)
    {
        case TokenKind::Minus:
            return QString("Negation");
        default:
            assert(!"String for TokenKind value was not defined yet");
            return QString();
    }
}

COMPILER_API QString StringifyBinaryOperation(TokenKind kind)
{
    switch (kind)
    {
        case TokenKind::Dot:
            return QString("Member Access");
        case TokenKind::Plus:
            return QString("Addition");
        case TokenKind::Minus:
            return QString("Subtraction");
        case TokenKind::Star:
            return QString("Multiplication");
        case TokenKind::Slash:
            return QString("Division");
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

Grouping::Grouping(
    const Token& openParenthesis,
    Expression* expression,
    const Token& closeParenthesis)
    : Expression(NodeKind::Grouping)
    , m_openParenthesis{ openParenthesis }
    , m_expression{ expression }
    , m_closeParenthesis{ closeParenthesis }
{
}

UnaryExpression::UnaryExpression(const Token& unaryOperator, Expression* expression)
    : Expression(NodeKind::UnaryExpression)
    , m_unaryOperator{ unaryOperator }
    , m_expression{ expression }
{
}

BinaryExpression::BinaryExpression(Expression* leftExpression, const Token& binaryOperator, Expression* rightExpression)
    : Expression(NodeKind::BinaryExpression)
    , m_leftExpression{ leftExpression }
    , m_binaryOperator{ binaryOperator }
    , m_rightExpression{ rightExpression }
{
}

MemberAccess::MemberAccess(
    const Token& dot,
    Expression* expression)
    : Expression(NodeKind::MemberAccess)
    , m_dot{ dot }
    , m_expression{ expression }
{
}

Name::Name(const Token& token)
    : Expression(NodeKind::Name)
    , m_token{ token }
{
}

Type::Type(Name* name)
    : Node(NodeKind::Type)
    , m_name{ name}
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

Number::Number(
    const Token& token,
    const Token& colon,
    const Type& type)
    : Expression(NodeKind::Number)
    , m_token{ token }
    , m_colon{ colon }
    , m_type{ type }
{
}

FieldDeclarationStatement::FieldDeclarationStatement(
    Name* name,
    const std::optional<Token>& colon,
    const std::optional<Type>& type,
    const std::optional<Token>& equals,
    const std::optional<Expression*>& expression)
    : Statement(NodeKind::FieldDeclarationStatement)
    , m_name{ name }
    , m_colon{ colon }
    , m_type{ type }
    , m_equals{ equals }
    , m_expression{ expression }
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

MethodDefinitionStatement::MethodDefinitionStatement(
    const Token& keyword,
    const Token& name,
    Parameters* parameters,
    Block* body)
    : Statement(NodeKind::MethodDefinitionStatement)
    , m_keyword{ keyword }
    , m_name{ name }
    , m_parameters{ parameters }
    , m_body{ body }
{
}

EnumDefinitionStatement::EnumDefinitionStatement(
    const Token& keyword,
    const Token& name,
    const std::optional<Type>& baseType,
    Block* body)
    : Statement(NodeKind::EnumDefinitionStatement)
    , m_keyword{ keyword }
    , m_name{ name }
    , m_baseType{ baseType }
    , m_body{ body }
{
}

EnumMember::EnumMember(Name* name)
    : Statement(NodeKind::EnumMember)
    , m_name{ name }
{
}

EnumMember::EnumMember(
    Name* name, 
    const Token& equal, 
    Number* value)
    : Statement(NodeKind::EnumMember)
    , m_name{ name }
    , m_equal{ equal }
    , m_value{ value }
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
