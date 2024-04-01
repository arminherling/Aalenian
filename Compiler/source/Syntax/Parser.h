#pragma once

#include <Defines.h>
#include <Compiler/DiagnosticsBag.h>
#include <Syntax/TokenBuffer.h>
#include <Syntax/ArgumentNode.h>
#include <Syntax/ArgumentsNode.h>
#include <Syntax/BoolLiteral.h>
#include <Syntax/BlockNode.h>
#include <Syntax/EnumFieldDefinitionStatement.h>
#include <Syntax/Expression.h>
#include <Syntax/GroupingExpression.h>
#include <Syntax/Statement.h>
#include <Syntax/NumberLiteral.h>
#include <Syntax/ParameterNode.h>
#include <Syntax/ParametersNode.h>
#include <Syntax/ParseTree.h>

class COMPILER_API Parser
{
public:
    Parser(const TokenBuffer& tokens, DiagnosticsBag& diagnostics);

    ParseTree Parse();

private:
    enum class StatementScope
    {
        Global,
        Function,
        Method,
        Enum,
        Type
    };

    QList<Statement*> ParseGlobalStatements();
    QList<Statement*> ParseStatements(StatementScope scope);
    Statement* ParseAssignmentStatement();
    Statement* ParseExpressionStatement();
    Statement* ParseFunctionDefinitionStatement();
    Statement* ParseEnumDefinitionStatement();
    Statement* ParseTypeDefinitionStatement();
    Statement* ParseFieldDeclarationStatement();
    Statement* ParseMethodDefinitionStatement();
    Statement* ParseIfStatement(StatementScope scope);
    Statement* ParseWhileStatement(StatementScope scope);
    Statement* ParseReturnStatement();
    Expression* ParseExpression();
    Expression* ParseBinaryExpression(i32 parentPrecedence);
    Expression* ParsePrimaryExpression();
    Expression* ParseFunctionCallOrNameExpression();
    Expression* ParseFunctionCallExpression();
    ParametersNode* ParseParametersNode();
    ArgumentsNode* ParseArgumentsNode();
    BlockNode* ParseFunctionBody();
    BlockNode* ParseEnumBody();
    BlockNode* ParseTypeBody();
    BlockNode* ParseMethodBody();
    BlockNode* ParseBlockNode(StatementScope scope);
    ParameterNode* ParseParameterNode();
    ArgumentNode* ParseArgumentNode();
    TypeName ParseTypeNode();
    NameExpression* ParseNameExpression();
    NumberLiteral* ParseNumberLiteral();
    GroupingExpression* ParseGroupingExpression();
    EnumFieldDefinitionStatement* ParseEnumFieldDefinitionStatement();

    Token AdvanceOnMatch(TokenKind kind);
    std::optional<BoolLiteral*> TryParseBoolLiteral();
    std::optional<Token> TryMatchKeyword(const QStringView& keyword);
    void SkipUntil(TokenKind kind);

    Token Peek(i32 offset);
    Token CurrentToken() { return Peek(0); }
    Token NextToken() { return Peek(1); }
    void AdvanceCurrentIndex() { m_currentIndex++; }

    bool HasLineBreakSinceLastMemberAccess();
    bool HasPossibleReturnValue(const Token& returnKeyword);

    TokenBuffer m_tokens;
    DiagnosticsBag& m_diagnostics;
    i32 m_currentIndex;
};

COMPILER_API ParseTree Parse(const TokenBuffer& tokens, DiagnosticsBag& diagnostics) noexcept;
