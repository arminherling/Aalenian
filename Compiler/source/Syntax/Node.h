#pragma once

#include <API.h>
#include <Syntax/Token.h>

#include <qlist.h>

enum class COMPILER_API NodeKind
{
    Unknown,
    Error,

    AssignmentStatement,
    ExpressionStatement,
    FunctionDefinitionStatement,
    TypeDefinitionStatement,
    FieldDeclarationStatement,
    MethodDefinitionStatement,
    ReturnStatement,

    Parameters,
    Arguments,
    Block,

    Discard,
    FunctionCall,
    Name,
    Number,
    Grouping,
    BinaryExpression,
    MemberAccess
};

COMPILER_API QString StringifyNodeKind(NodeKind kind);
COMPILER_API QString StringifyOperation(TokenKind kind);


class COMPILER_API Node
{
public:
    Node(NodeKind kind);

    NodeKind kind() { return m_kind; }

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

class COMPILER_API Name : public Expression
{
public:
    Name(const Token& token);

    [[nodiscard]] const Token& identifier() noexcept { return m_token; }

private:
    Token m_token;
};

class COMPILER_API FieldDeclarationStatement : public Statement
{
public:
    FieldDeclarationStatement(
        Name* name, 
        const std::optional<Token>& colon, 
        const std::optional<Name*>& type,
        const std::optional<Token>& equals, 
        const std::optional<Expression*>& expression);

    [[nodiscard]] Name* name() noexcept { return m_name; }
    [[nodiscard]] const std::optional<Token>& colon() noexcept { return m_colon; }
    [[nodiscard]] const std::optional<Name*>& type() noexcept { return m_type; }
    [[nodiscard]] const std::optional<Token>& equals() noexcept { return m_equals; }
    [[nodiscard]] const std::optional<Expression*>& expression() noexcept { return m_expression; }

private:
    Name* m_name;
    std::optional<Token> m_colon;
    std::optional<Name*> m_type;
    std::optional<Token> m_equals;
    std::optional<Expression*> m_expression;
};

class COMPILER_API AssignmentStatement : public Statement
{
public:
    AssignmentStatement(Expression* leftExpression, const Token& equalsToken, Expression* rightExpression);

    [[nodiscard]] Expression* leftExpression() noexcept { return m_leftExpression; }
    [[nodiscard]] Expression* rightExpression() noexcept { return m_rightExpression; }

private:
    Expression* m_leftExpression;
    Token m_equalsToken;
    Expression* m_rightExpression;
};

class COMPILER_API ExpressionStatement : public Statement
{
public:
    ExpressionStatement(Expression* expression);

    [[nodiscard]] Expression* expression() noexcept { return m_expression; }

private:
    Expression* m_expression;
};

class COMPILER_API ReturnStatement : public Statement
{
public:
    ReturnStatement(const Token& returnKeyword, Expression* expression);

    [[nodiscard]] Expression* expression() noexcept { return m_expression; }

private:
    Token m_returnKeyword;
    Expression* m_expression;
};

class COMPILER_API Discard : public Expression
{
public:
    Discard(const Token& token);
};

class COMPILER_API Grouping : public Expression
{
public:
    Grouping(const Token& openParenthesis, Expression* expression, const Token& closeParenthesis);

    [[nodiscard]] const Token& openParenthesis() noexcept { return m_openParenthesis; }
    [[nodiscard]] Expression* expression() noexcept { return m_expression; }
    [[nodiscard]] const Token& closeParenthesis() noexcept { return m_closeParenthesis; }

private:
    Token m_openParenthesis;
    Expression* m_expression;
    Token m_closeParenthesis;
};

class COMPILER_API BinaryExpression : public Expression
{
public:
    BinaryExpression(Expression* leftExpression, const Token& binaryOperator, Expression* rightExpression);

    [[nodiscard]] Expression* leftExpression() noexcept { return m_leftExpression; }
    [[nodiscard]] const Token& binaryOperator() noexcept { return m_binaryOperator; }
    [[nodiscard]] Expression* rightExpression() noexcept { return m_rightExpression; }

private:
    Expression* m_leftExpression;
    Token m_binaryOperator;
    Expression* m_rightExpression;
};

class COMPILER_API MemberAccess : public Expression
{
public:
    MemberAccess(const Token& dot, Expression* expression);

    [[nodiscard]] const Token& dot() noexcept { return m_dot; }
    [[nodiscard]] Expression* expression() noexcept { return m_expression; }

private:
    Token m_dot;
    Expression* m_expression;
};


class COMPILER_API Parameters : public Node
{
public:
    Parameters(const Token& openParenthesis, const Token& closeParenthesis);

    [[nodiscard]] const Token& openParenthesis() noexcept { return m_openParenthesis; }
    [[nodiscard]] const Token& closeParenthesis() noexcept { return m_closeParenthesis; }

private:
    Token m_openParenthesis;
    Token m_closeParenthesis;
};

class COMPILER_API Arguments : public Node
{
public:
    Arguments(const Token& openParenthesis, const Token& closeParenthesis);

    [[nodiscard]] const Token& openParenthesis() noexcept { return m_openParenthesis; }
    [[nodiscard]] const Token& closeParenthesis() noexcept { return m_closeParenthesis; }

private:
    Token m_openParenthesis;
    Token m_closeParenthesis;
};

class COMPILER_API Block : public Node
{
public:
    Block(const Token& openBracket, const QList<Statement*>& statements, const Token& closeBracket);

    [[nodiscard]] const Token& openBracket() noexcept { return m_openBracket; }
    [[nodiscard]] const QList<Statement*>& statements() noexcept { return m_statements; }
    [[nodiscard]] const Token& closeBracket() noexcept { return m_closeBracket; }

private:
    Token m_openBracket;
    QList<Statement*> m_statements;
    Token m_closeBracket;
};

class COMPILER_API FunctionCall : public Expression
{
public:
    FunctionCall(const Token& nameToken, Arguments* arguments);

    [[nodiscard]] const Token& name() noexcept { return m_nameToken; }
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

class COMPILER_API MethodDefinitionStatement : public Statement
{
public:
    MethodDefinitionStatement(const Token& keyword, const Token& name, Parameters* parameters, Block* body);

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


class COMPILER_API TypeDefinitionStatement : public Statement
{
public:
    TypeDefinitionStatement(const Token& keyword, const Token& name, Block* body);

    [[nodiscard]] const Token& keyword() noexcept { return m_keyword; }
    [[nodiscard]] const Token& name() noexcept { return m_name; }
    [[nodiscard]] Block* body() noexcept { return m_body; }

private:
    Token m_keyword;
    Token m_name;
    Block* m_body;
};

class COMPILER_API Number : public Expression
{
public:
    Number(const Token& token);
    Number(const Token& token, const Token& colon, Name* type);

    [[nodiscard]] const Token& token() noexcept { return m_token; }
    [[nodiscard]] const std::optional<Token>& colon() noexcept { return m_colon; }
    [[nodiscard]] const std::optional<Name*>& type() noexcept { return m_type; }

private:
    Token m_token;
    std::optional<Token> m_colon;
    std::optional<Name*> m_type;
};

class COMPILER_API Error : public Expression
{
public:
    Error(const Token& token);

    [[nodiscard]] const Token& token() noexcept { return m_token; }

private:
    Token m_token;
};
