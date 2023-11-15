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
    EnumDefinitionStatement,
    TypeDefinitionStatement,
    FieldDeclarationStatement,
    MethodDefinitionStatement,
    IfStatement,
    WhileStatement,
    ReturnStatement,

    UnaryExpression,
    BinaryExpression,
    Type,
    Parameter,
    Parameters,
    Argument,
    Arguments,
    Block,
    EnumMember,

    Discard,
    FunctionCall,
    Name,
    Bool,
    Number,
    Grouping,
    ScopeAccess,
    MemberAccess
};

COMPILER_API QString StringifyNodeKind(NodeKind kind);
COMPILER_API QString StringifyUnaryOperation(TokenKind kind);
COMPILER_API QString StringifyBinaryOperation(TokenKind kind);


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

class COMPILER_API Type : public Node
{
public:
    Type(const std::optional<Token>& ref, Name* name);

    [[nodiscard]] const std::optional<Token>& ref() const noexcept { return m_ref; }
    [[nodiscard]] bool isReference() const noexcept { return m_ref.has_value(); }
    [[nodiscard]] Name* name() const noexcept { return m_name; }

private:
    std::optional<Token> m_ref;
    Name* m_name;
};

class COMPILER_API Parameter : public Node
{
public:
    Parameter(Name* name, const Token& colon, const Type& type);

    [[nodiscard]] Name* name() const noexcept { return m_name; }
    [[nodiscard]] const Token& colon() noexcept { return m_colon; }
    [[nodiscard]] const Type& type() noexcept { return m_type; }

private:
    Name* m_name;
    Token m_colon;
    Type m_type;
};

class COMPILER_API Argument : public Node
{
public:
    Argument(const std::optional<Token>& ref, Expression* expression);

    [[nodiscard]] const std::optional<Token>& ref() const noexcept { return m_ref; }
    [[nodiscard]] bool isReference() const noexcept { return m_ref.has_value(); }
    [[nodiscard]] Expression* expression() const noexcept { return m_expression; }

private:
    std::optional<Token> m_ref;
    Expression* m_expression;
};

class COMPILER_API FieldDeclarationStatement : public Statement
{
public:
    FieldDeclarationStatement(
        Name* name, 
        const std::optional<Token>& colon, 
        const std::optional<Type>& type,
        const std::optional<Token>& equals, 
        const std::optional<Expression*>& expression);

    [[nodiscard]] Name* name() noexcept { return m_name; }
    [[nodiscard]] const std::optional<Token>& colon() noexcept { return m_colon; }
    [[nodiscard]] const std::optional<Type>& type() noexcept { return m_type; }
    [[nodiscard]] const std::optional<Token>& equals() noexcept { return m_equals; }
    [[nodiscard]] const std::optional<Expression*>& expression() noexcept { return m_expression; }

private:
    Name* m_name;
    std::optional<Token> m_colon;
    std::optional<Type> m_type;
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

class COMPILER_API IfStatement : public Statement
{
public:
    IfStatement(const Token& ifKeyword, Expression* condition, Block* body);

    [[nodiscard]] Expression* condition() noexcept { return m_condition; }
    [[nodiscard]] Block* body() noexcept { return m_body; }

private:
    Token m_ifKeyword;
    Expression* m_condition;
    Block* m_body;
};

class COMPILER_API WhileStatement : public Statement
{
public:
    WhileStatement(const Token& ifKeyword, Expression* condition, Block* body);

    [[nodiscard]] Expression* condition() noexcept { return m_condition; }
    [[nodiscard]] Block* body() noexcept { return m_body; }

private:
    Token m_ifKeyword;
    Expression* m_condition;
    Block* m_body;
};

class COMPILER_API ReturnStatement : public Statement
{
public:
    ReturnStatement(const Token& returnKeyword, const std::optional<Expression*>& expression);

    [[nodiscard]] std::optional<Expression*> expression() noexcept { return m_expression; }

private:
    Token m_returnKeyword;
    std::optional<Expression*> m_expression;
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

class COMPILER_API UnaryExpression : public Expression
{
public:
    UnaryExpression(const Token& unaryOperator, Expression* expression);

    [[nodiscard]] const Token& unaryOperator() noexcept { return m_unaryOperator; }
    [[nodiscard]] Expression* expression() noexcept { return m_expression; }

private:
    Token m_unaryOperator;
    Expression* m_expression;
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

class COMPILER_API ScopeAccess : public Expression
{
public:
    ScopeAccess(const Token& doubleColon, Expression* expression);

    [[nodiscard]] const Token& doubleColon() noexcept { return m_doubleColon; }
    [[nodiscard]] Expression* expression() noexcept { return m_expression; }

private:
    Token m_doubleColon;
    Expression* m_expression;
};

class COMPILER_API Parameters : public Node
{
public:
    Parameters(
        const Token& openParenthesis, 
        const QList<Parameter*>& parameters,
        const Token& closeParenthesis);

    [[nodiscard]] const Token& openParenthesis() noexcept { return m_openParenthesis; }
    [[nodiscard]] const QList<Parameter*>& parameters() noexcept { return m_parameters; }
    [[nodiscard]] const Token& closeParenthesis() noexcept { return m_closeParenthesis; }

private:
    Token m_openParenthesis;
    const QList<Parameter*> m_parameters;
    Token m_closeParenthesis;
};

class COMPILER_API Arguments : public Node
{
public:
    Arguments(
        const Token& openParenthesis, 
        const QList<Argument*>& arguments,
        const Token& closeParenthesis);

    [[nodiscard]] const Token& openParenthesis() noexcept { return m_openParenthesis; }
    [[nodiscard]] const QList<Argument*>& arguments() noexcept { return m_arguments; }
    [[nodiscard]] const Token& closeParenthesis() noexcept { return m_closeParenthesis; }

private:
    Token m_openParenthesis;
    QList<Argument*> m_arguments;
    Token m_closeParenthesis;
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

class COMPILER_API EnumDefinitionStatement : public Statement
{
public:
    EnumDefinitionStatement(
        const Token& keyword, 
        const Token& name, 
        const std::optional<Type>& type, 
        Block* body);

    [[nodiscard]] const Token& keyword() noexcept { return m_keyword; }
    [[nodiscard]] const Token& name() noexcept { return m_name; }
    [[nodiscard]] const std::optional<Type>& baseType() noexcept { return m_baseType; }
    [[nodiscard]] Block* body() noexcept { return m_body; }

private:
    Token m_keyword;
    Token m_name;
    std::optional<Type> m_baseType;
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

class COMPILER_API Bool : public Expression
{
public:
    Bool(bool value);

    [[nodiscard]]bool value() noexcept { return m_value; }

private:
    bool m_value;
};

class COMPILER_API Number : public Expression
{
public:
    Number(const Token& token);
    Number(const Token& token, const Token& colon, const Type& type);

    [[nodiscard]] const Token& token() noexcept { return m_token; }
    [[nodiscard]] const std::optional<Token>& colon() noexcept { return m_colon; }
    [[nodiscard]] const std::optional<Type>& type() noexcept { return m_type; }

private:
    Token m_token;
    std::optional<Token> m_colon;
    std::optional<Type> m_type;
};

class COMPILER_API EnumMember : public Statement
{
public:
    EnumMember(Name* name);
    EnumMember(Name* name, const Token& equal, Number* value);

    [[nodiscard]] Name* name() noexcept { return m_name; }
    [[nodiscard]] const std::optional<Token>& equal() noexcept { return m_equal; }
    [[nodiscard]] const std::optional<Number*>& value() noexcept { return m_value; }

private:
    Name* m_name;
    std::optional<Token> m_equal;
    std::optional<Number*> m_value;
};

class COMPILER_API Error : public Expression
{
public:
    Error(const Token& token);

    [[nodiscard]] const Token& token() noexcept { return m_token; }

private:
    Token m_token;
};
