#pragma once

#include <API.h>
#include <Compiler/DiagnosticsBag.h>
#include <Syntax/TokenBuffer.h>
#include <Syntax/ParseTree.h>
#include <Syntax/Node.h>

class COMPILER_API Parser
{
public:
    Parser(const TokenBuffer& tokens, DiagnosticsBag& diagnostics);

    ParseTree Parse();

private:
    enum StatementScope
    {
        Global,
        Function,
        Method,
        Type
    };

    QList<Statement*> ParseGlobalStatements();
    QList<Statement*> ParseStatements(StatementScope scope);
    Statement* ParseAssignmentStatement(StatementScope scope);
    Statement* ParseExpressionStatement(StatementScope scope);
    Statement* ParseFunctionDefinitionStatement();
    Statement* ParseTypeDefinitionStatement();
    Statement* ParseFieldDeclarationStatement();
    Statement* ParseMethodDefinitionStatement();
    Statement* ParseReturnStatement(StatementScope scope);
    Expression* ParseExpression(StatementScope scope);
    Expression* ParseBinaryExpression(StatementScope scope, int parentPrecedence);
    Expression* ParsePrimaryExpression(StatementScope scope);
    Expression* ParseFunctionCallOrName();
    Expression* ParseFunctionCall();
    Parameters* ParseParameters();
    Arguments* ParseArguments();
    Block* ParseFunctionBody();
    Block* ParseTypeBody();
    Block* ParseMethodBody();
    Block* ParseBlock(StatementScope scope);
    Expression* ParseType();
    Expression* ParseName();
    Expression* ParseNumberLiteral();

    Token AdvanceOnMatch(TokenKind kind);
    void SkipUntil(TokenKind kind);

    Token Peek(int offset);
    Token CurrentToken() { return Peek(0); }
    Token NextToken() { return Peek(1); }
    void AdvanceCurrentIndex() { m_currentIndex++; }

    TokenBuffer m_tokens;
    DiagnosticsBag& m_diagnostics;
    int m_currentIndex;
};

COMPILER_API ParseTree Parse(const TokenBuffer& tokens, DiagnosticsBag& diagnostics) noexcept;
