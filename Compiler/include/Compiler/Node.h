#pragma once

#include "CompilerApi.h"
#include "Token.h"

enum class COMPILER_API NodeKind
{
    Unknown,
    AssignmentStatement,
    ExpressionStatement,
    FunctionDefinitionStatement,
    ReturnStatement,
    Discard,
    Parameters,
    Arguments,
    Block,
    FunctionCall,
    Name,
    Number
};

class COMPILER_API Node
{
public:
    Node(NodeKind kind);

    NodeKind Kind() { return m_kind; }

private:
    NodeKind m_kind;
};

class COMPILER_API Statement : public Node
{
public:
    Statement(NodeKind kind);
};

class COMPILER_API Expression : public Node
{
public:
    Expression(NodeKind kind);
};

class COMPILER_API AssignmentStatement : public Statement
{
public:
    AssignmentStatement(Expression* leftExpression, const Token& equalsToken, Expression* rightExpression);

private:
    Expression* m_leftExpression;
    Token m_equalsToken;
    Expression* m_rightExpression;
};

class COMPILER_API ExpressionStatement : public Statement
{
public:
    ExpressionStatement(Expression* expression);

private:
    Expression* m_expression;
};

class COMPILER_API ReturnStatement : public Statement
{
public:
    ReturnStatement(const Token& returnKeyword, Expression* expression);

private:
    Token m_returnKeyword;
    Expression* m_expression;
};

class COMPILER_API Discard : public Expression
{
public:
    Discard(const Token& token);
};

class COMPILER_API Name : public Expression
{
public:
    Name(const Token& token);

    [[nodiscard]] const Token& Identifier() noexcept { return m_token; }

private:
    Token m_token;
};

class COMPILER_API Parameters : public Node
{
public:
    Parameters(const Token& openParenthesis, const Token& closeParenthesis);

    [[nodiscard]] const Token& OpenParenthesis() noexcept { return m_openParenthesis; }
    [[nodiscard]] const Token& CloseParenthesis() noexcept { return m_closeParenthesis; }

private:
    Token m_openParenthesis;
    Token m_closeParenthesis;
};

class COMPILER_API Arguments : public Node
{
public:
    Arguments(const Token& openParenthesis, const Token& closeParenthesis);

    [[nodiscard]] const Token& OpenParenthesis() noexcept { return m_openParenthesis; }
    [[nodiscard]] const Token& CloseParenthesis() noexcept { return m_closeParenthesis; }

private:
    Token m_openParenthesis;
    Token m_closeParenthesis;
};

class COMPILER_API Block : public Node
{
public:
    Block(const Token& openBracket, const Token& closeBracket);

    [[nodiscard]] const Token& OpenBracket() noexcept { return m_openBracket; }
    [[nodiscard]] const Token& CloseBracket() noexcept { return m_closeBracket; }

private:
    Token m_openBracket;
    Token m_closeBracket;
};

class COMPILER_API FunctionCall : public Expression
{
public:
    FunctionCall(const Token& nameToken, Arguments* arguments);

    [[nodiscard]] const Token& Name() noexcept { return m_nameToken; }
    [[nodiscard]] Arguments* arguments() { return m_arguments; }

private:
    Token m_nameToken;
    Arguments* m_arguments;
};

class COMPILER_API FunctionDefinitionStatement : public Statement
{
public:
    FunctionDefinitionStatement(const Token& keyword, const Token& name, Parameters* parameters, Block* body);

    [[nodiscard]] const Token& keyword() noexcept { return m_keyword; }
    [[nodiscard]] const Token& name() noexcept { return m_name; }
    [[nodiscard]] Parameters* parameters()  noexcept { return m_parameters; }
    [[nodiscard]] Block* body() noexcept { return m_body; }

private:
    Token m_keyword;
    Token m_name;
    Parameters* m_parameters;
    Block* m_body;
};

class COMPILER_API Number : public Expression
{
public:
    Number(const Token& token);

    [[nodiscard]] const Token& token() noexcept { return m_token; }

private:
    Token m_token;
};
