#pragma once

#include <Defines.h>
#include <Compiler/DiagnosticsBag.h>
#include <Syntax/ArgumentNode.h>
#include <Syntax/ArgumentsNode.h>
#include <Syntax/BinaryExpression.h>
#include <Syntax/BlockNode.h>
#include <Syntax/BoolLiteral.h>
#include <Syntax/EnumFieldDefinitionStatement.h>
#include <Syntax/Expression.h>
#include <Syntax/GroupingExpression.h>
#include <Syntax/NumberLiteral.h>
#include <Syntax/ParameterNode.h>
#include <Syntax/ParametersNode.h>
#include <Syntax/ParseTree.h>
#include <Syntax/Statement.h>
#include <Syntax/TokenBuffer.h>
#include <Syntax/UnaryExpression.h>

class COMPILER_API Parser
{
public:
    Parser(const TokenBuffer& tokens, DiagnosticsBag& diagnostics);

    ParseTree parse();

private:
    enum class StatementScope
    {
        Global,
        Function,
        Method,
        Type
    };

    QList<Statement*> parseGlobalStatements();
    QList<Statement*> parseStatements(StatementScope scope);
    Statement* parseAssignmentStatement();
    Statement* parseExpressionStatement();
    Statement* parseFunctionDefinitionStatement();
    Statement* parseEnumDefinitionStatement();
    QList<EnumFieldDefinitionStatement*> parseEnumFieldDefinitions();
    Statement* parseTypeDefinitionStatement();
    Statement* parseFieldDeclarationStatement();
    Statement* parseMethodDefinitionStatement();
    Statement* parseIfStatement(StatementScope scope);
    Statement* parseWhileStatement(StatementScope scope);
    Statement* parseReturnStatement();
    Expression* parseExpression();
    Expression* parseBinaryExpression(i32 parentPrecedence);
    Expression* parsePrimaryExpression();
    Expression* parseFunctionCallOrNameExpression();
    Expression* parseFunctionCallExpression();
    ParametersNode* parseParametersNode();
    ArgumentsNode* parseArgumentsNode();
    BlockNode* parseFunctionBody();
    BlockNode* parseTypeBody();
    BlockNode* parseMethodBody();
    BlockNode* parseBlockNode(StatementScope scope);
    ParameterNode* parseParameterNode();
    ArgumentNode* parseArgumentNode();
    TypeName parseTypeNode();
    NameExpression* parseNameExpression();
    NumberLiteral* parseNumberLiteral();
    GroupingExpression* parseGroupingExpression();
    EnumFieldDefinitionStatement* parseEnumFieldDefinitionStatement();

    Token advanceOnMatch(TokenKind kind);
    std::optional<BoolLiteral*> tryParseBoolLiteral();
    std::optional<Token> tryMatchKeyword(const QStringView& keyword);
    void skipUntil(TokenKind kind);

    Token peek(i32 offset);
    Token currentToken() { return peek(0); }
    Token nextToken() { return peek(1); }
    void advanceCurrentIndex() { m_currentIndex++; }

    bool hasLineBreakSinceLastMemberAccess();
    bool hasPossibleReturnValue(const Token& returnKeyword);

    i32 unaryOperatorPrecedence(Token token) const;
    i32 binaryOperatorPrecedence(TokenKind kind) const;
    UnaryOperatornKind convertUnaryOperatorTokenKindToEnum(Token token) const;
    BinaryOperatornKind convertBinaryOperatorTokenKindToEnum(TokenKind kind) const;

    TokenBuffer m_tokens;
    DiagnosticsBag& m_diagnostics;
    i32 m_currentIndex;
};

COMPILER_API ParseTree Parse(const TokenBuffer& tokens, DiagnosticsBag& diagnostics) noexcept;
