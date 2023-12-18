#pragma once

#include <Defines.h>
#include <Compiler/DiagnosticsBag.h>
#include <Syntax/TokenBuffer.h>
#include <Syntax/ArgumentNode.h>
#include <Syntax/ArgumentsNode.h>
#include <Syntax/Bool.h>
#include <Syntax/Block.h>
#include <Syntax/EnumMember.h>
#include <Syntax/Expression.h>
#include <Syntax/Grouping.h>
#include <Syntax/Statement.h>
#include <Syntax/Number.h>
#include <Syntax/Parameter.h>
#include <Syntax/Parameters.h>
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
    Expression* ParseFunctionCallOrName();
    Expression* ParseFunctionCall();
    Parameters* ParseParameters();
    ArgumentsNode* ParseArgumentsNode();
    Block* ParseFunctionBody();
    Block* ParseEnumBody();
    Block* ParseTypeBody();
    Block* ParseMethodBody();
    Block* ParseBlock(StatementScope scope);
    Parameter* ParseParameter();
    ArgumentNode* ParseArgumentNode();
    Type ParseType();
    Name* ParseName();
    Number* ParseNumberLiteral();
    Grouping* ParseGrouping();
    EnumMember* ParseEnumMember();

    Token AdvanceOnMatch(TokenKind kind);
    std::optional<Bool*> TryParseBool();
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
