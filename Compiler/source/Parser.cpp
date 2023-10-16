#include "Parser.h"

Parser::Parser(const TokenBuffer& tokens, DiagnosticsBag& diagnostics)
    : m_tokens{ tokens }
    , m_diagnostics{ diagnostics }
    , m_currentIndex{ 0 }
{
}

ParseTree Parser::Parse()
{
    auto globalStatements = ParseGlobalStatements();

    return ParseTree(globalStatements);
}

QList<Statement*> Parser::ParseGlobalStatements()
{
    QList<Statement*> statements;

    auto currentToken = CurrentToken();
    while (true)
    {
        switch (currentToken.kind)
        {
            case TokenKind::Identifier:
            {
                auto nameOrCallExpression = ParseFunctionCallOrName();

                auto nextToken = CurrentToken();
                if (nextToken.kind == TokenKind::Equal)
                {
                    // skip equals token
                    AdvanceCurrentIndex();
                    statements.append(ParseAssignmentStatement(nameOrCallExpression, nextToken));
                }

                break;
            }
            case TokenKind::EndOfFile:
            {
                return statements;
            }
            default:
            {
                AdvanceCurrentIndex();
                break;
            }
        }

        currentToken = CurrentToken();
    }
}

Statement* Parser::ParseAssignmentStatement(Expression* leftExpression, const Token& equals)
{
    auto rightExpression = ParseExpression();
    return new AssignmentStatement(leftExpression, equals, rightExpression);
}

Expression* Parser::ParseExpression()
{
    return ParseBinaryExpression(0);
}

Expression* Parser::ParseBinaryExpression(int parentPrecedence)
{
    return ParsePrimaryExpression();
}

Expression* Parser::ParsePrimaryExpression()
{
    auto currentToken = CurrentToken();

    switch (currentToken.kind)
    {
        case TokenKind::Identifier:
        {
            return ParseFunctionCallOrName();
        }
        case TokenKind::Number:
        {
            return ParseNumberLiteral();
        }
        default:
        {
            // error
            AdvanceCurrentIndex();
            return nullptr;
        }
    }
}

Expression* Parser::ParseFunctionCallOrName()
{
    auto name = ParseName();
    auto nextToken = CurrentToken();

    //if (nextToken.kind == TokenKind::OpenParenthesis)
    //    return ParseFunctionCallExpression(name);

    return name;
}

Expression* Parser::ParseName()
{
    auto name = AdvanceOnMatch(TokenKind::Identifier);
    return new Name(name);
}

Expression* Parser::ParseNumberLiteral()
{
    auto number = AdvanceOnMatch(TokenKind::Number);
    return new Number(number);
}

Token Parser::AdvanceOnMatch(TokenKind kind)
{
    auto currentToken = CurrentToken();

    if (currentToken.kind == kind)
    {
        AdvanceCurrentIndex();
        return currentToken;
    }
    else
    {
        // error expected x but got y
        return Token::ToError(currentToken);
    }
}

Token Parser::Peek(int offset)
{
    auto index = m_currentIndex + offset;
    if (index >= m_tokens.size())
        return Token{ .kind = TokenKind::EndOfFile };

    return m_tokens[index];
}

COMPILER_API ParseTree Parse(const TokenBuffer& tokens, DiagnosticsBag& diagnostics) noexcept
{
    Parser parser{ tokens, diagnostics };
    return parser.Parse();
}
