#pragma once

#include "CompilerApi.h"
#include "TokenBuffer.h"
#include "DiagnosticsBag.h"
#include "ParseTree.h"

#include "Node.h"
#include <QList>

class COMPILER_API Parser
{
public:
    Parser(const TokenBuffer& tokens, DiagnosticsBag& diagnostics);

    ParseTree Parse();

private:
    enum StatementScope
    {
        Global,
        Function
    };

    QList<Statement*> ParseGlobalStatements();
    QList<Statement*> ParseStatements(StatementScope scope);
    Statement* ParseAssignmentStatement();
    Statement* ParseExpressionStatement();
    Statement* ParseFunctionDefinitionStatement();
    Statement* ParseReturnStatement();
    Expression* ParseExpression();
    Expression* ParseBinaryExpression(int parentPrecedence);
    Expression* ParsePrimaryExpression();
    Expression* ParseFunctionCallOrName();
    Expression* ParseFunctionCall();
    Parameters* ParseParameters();
    Arguments* ParseArguments();
    Block* ParseFunctionBody();
    Block* ParseBlock(StatementScope scope);
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
