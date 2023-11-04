#include <Syntax/Parser.h>

bool IsFunctionDefinitionKeyword(const QStringView& lexeme)
{
    return lexeme == QString("define");
}

bool IsTypeDefinitionKeyword(const QStringView& lexeme)
{
    return lexeme == QString("type");
}

bool IsReturnKeyword(const QStringView& lexeme)
{
    return lexeme == QString("return");
}

Parser::Parser(const TokenBuffer& tokens, DiagnosticsBag& diagnostics)
    : m_tokens{ tokens }
    , m_diagnostics{ diagnostics }
    , m_currentIndex{ 0 }
{
}

ParseTree Parser::Parse()
{
    auto globalStatements = ParseGlobalStatements();

    return ParseTree(m_tokens, globalStatements);
}
QList<Statement*> Parser::ParseGlobalStatements()
{
    return ParseStatements(StatementScope::Global);
}

QList<Statement*> Parser::ParseStatements(StatementScope scope)
{
    QList<Statement*> statements;

    auto currentToken = CurrentToken();
    while (true)
    {
        switch (currentToken.kind)
        {
            case TokenKind::Underscore:
            {
                statements.append(ParseAssignmentStatement(scope));
                break;
            }
            case TokenKind::Identifier:
            {
                if (scope == StatementScope::Global)
                {
                    if (IsFunctionDefinitionKeyword(m_tokens.GetLexeme(currentToken.kindIndex)))
                    {
                        statements.append(ParseFunctionDefinitionStatement());
                        break;
                    }
                    else if (IsTypeDefinitionKeyword(m_tokens.GetLexeme(currentToken.kindIndex)))
                    {
                        statements.append(ParseTypeDefinitionStatement());
                        break;
                    }
                }
                else if (scope == StatementScope::Function || scope == StatementScope::Method)
                {
                    if (IsReturnKeyword(m_tokens.GetLexeme(currentToken.kindIndex)))
                    {
                        statements.append(ParseReturnStatement(scope));
                        break;
                    }
                }
                else if (scope == StatementScope::Type)
                {
                    if (IsFunctionDefinitionKeyword(m_tokens.GetLexeme(currentToken.kindIndex)))
                    {
                        statements.append(ParseMethodDefinitionStatement());
                        break;
                    }

                    statements.append(ParseFieldDeclarationStatement());
                    break;
                }


                auto nextToken = NextToken();
                if (nextToken.kind == TokenKind::Equal)
                {
                    statements.append(ParseAssignmentStatement(scope));
                }
                else if (nextToken.kind == TokenKind::OpenParenthesis)
                {
                    auto expressionStatement = ParseExpressionStatement(scope);
                    statements.append(expressionStatement);
                }
                else
                {
                    const auto& location = m_tokens.GetSourceLocation(currentToken.locationIndex);
                    m_diagnostics.AddError(DiagnosticKind::Unknown, location);

                    AdvanceCurrentIndex();
                }
                break;
            }
            case TokenKind::CloseBracket:
            {
                if (scope == StatementScope::Global)
                {
                    const auto& location = m_tokens.GetSourceLocation(currentToken.locationIndex);
                    m_diagnostics.AddError(DiagnosticKind::Unknown, location);

                    AdvanceCurrentIndex();
                    break;
                }
            }
            case TokenKind::EndOfFile:
            {
                return statements;
            }
            default:
            {
                const auto& location = m_tokens.GetSourceLocation(currentToken.locationIndex);
                m_diagnostics.AddError(DiagnosticKind::Unknown, location);

                AdvanceCurrentIndex();
                break;
            }
        }

        currentToken = CurrentToken();
    }
}

Statement* Parser::ParseAssignmentStatement(StatementScope scope)
{
    auto leftExpression = ParsePrimaryExpression(scope);
    auto equals = AdvanceOnMatch(TokenKind::Equal);
    auto rightExpression = ParseExpression(scope);
    return new AssignmentStatement(leftExpression, equals, rightExpression);
}

Statement* Parser::ParseExpressionStatement(StatementScope scope)
{
    auto expression = ParseExpression(scope);
    return new ExpressionStatement(expression);
}

Statement* Parser::ParseFunctionDefinitionStatement()
{
    auto keyword = AdvanceOnMatch(TokenKind::Identifier);
    auto name = AdvanceOnMatch(TokenKind::Identifier);
    auto signature = ParseParameters();
    auto body = ParseFunctionBody();

    return new FunctionDefinitionStatement(keyword, name, signature, body);
}

Statement* Parser::ParseTypeDefinitionStatement()
{
    auto keyword = AdvanceOnMatch(TokenKind::Identifier);
    auto name = AdvanceOnMatch(TokenKind::Identifier);
    auto body = ParseTypeBody();

    return new TypeDefinitionStatement(keyword, name, body);
}

Statement* Parser::ParseFieldDeclarationStatement()
{
    auto name = (Name*)ParseName();
    auto current = CurrentToken();
    std::optional<Token> colon;
    std::optional<Name*> type;
    if (current.kind == TokenKind::Colon)
    {
        AdvanceCurrentIndex();
        colon = current;
        type = (Name*)ParseType();
        current = CurrentToken();
    }

    std::optional<Token> equals;
    std::optional<Expression*> expression;
    if (current.kind == TokenKind::Equal)
    {
        equals = current;
        AdvanceCurrentIndex();
        expression = ParseExpression(StatementScope::Type);
    }

    return new FieldDeclarationStatement(name, colon, type, equals, expression);
}

Statement* Parser::ParseMethodDefinitionStatement()
{
    auto keyword = AdvanceOnMatch(TokenKind::Identifier);
    auto name = AdvanceOnMatch(TokenKind::Identifier);
    auto signature = ParseParameters();
    auto body = ParseMethodBody();

    return new MethodDefinitionStatement(keyword, name, signature, body);
}

Statement* Parser::ParseReturnStatement(StatementScope scope)
{
    auto keyword = AdvanceOnMatch(TokenKind::Identifier);
    auto expression = ParseExpression(scope);
    return new ReturnStatement(keyword, expression);
}

Parameters* Parser::ParseParameters()
{
    auto openParenthesis = AdvanceOnMatch(TokenKind::OpenParenthesis);

    // TODO
    SkipUntil(TokenKind::CloseParenthesis);

    auto closeParenthesis = AdvanceOnMatch(TokenKind::CloseParenthesis);

    return new Parameters(openParenthesis, closeParenthesis);
}


Expression* Parser::ParseExpression(StatementScope scope)
{
    return ParseBinaryExpression(scope, 0);
}

Expression* Parser::ParseBinaryExpression(StatementScope scope, int parentPrecedence)
{
    return ParsePrimaryExpression(scope);
}

Expression* Parser::ParsePrimaryExpression(StatementScope scope)
{
    auto currentToken = CurrentToken();

    switch (currentToken.kind)
    {
        case TokenKind::Underscore:
        {
            AdvanceCurrentIndex();
            return new Discard(currentToken);
        }
        case TokenKind::Identifier:
        {
            return ParseFunctionCallOrName();
        }
        case TokenKind::Number:
        {
            return ParseNumberLiteral();
        }
        case TokenKind::Dot:
        {
            if (scope == StatementScope::Method)
            {
                AdvanceCurrentIndex();
                auto expression = ParseFunctionCallOrName();
                return new MemberAccess(currentToken, expression);
            }
        }
        default:
        {
            const auto& location = m_tokens.GetSourceLocation(currentToken.locationIndex);
            m_diagnostics.AddError(DiagnosticKind::Unknown, location);

            AdvanceCurrentIndex();
            return new Error(currentToken);
        }
    }
}

Expression* Parser::ParseFunctionCallOrName()
{
    auto nextToken = NextToken();

    if (nextToken.kind == TokenKind::OpenParenthesis)
    {
        return ParseFunctionCall();
    }
    else
    {
        return ParseName();
    }
}

Expression* Parser::ParseFunctionCall()
{
    auto name = AdvanceOnMatch(TokenKind::Identifier);
    auto arguments = ParseArguments();
    return new FunctionCall(name, arguments);
}

Arguments* Parser::ParseArguments()
{
    auto openParenthesis = AdvanceOnMatch(TokenKind::OpenParenthesis);

    SkipUntil(TokenKind::CloseParenthesis);

    auto closeParenthesis = AdvanceOnMatch(TokenKind::CloseParenthesis);

    return new Arguments(openParenthesis, closeParenthesis);
}

Expression* Parser::ParseType()
{
    return ParseName();
}

Expression* Parser::ParseName()
{
    auto name = AdvanceOnMatch(TokenKind::Identifier);
    return new Name(name);
}

Expression* Parser::ParseNumberLiteral()
{
    auto number = AdvanceOnMatch(TokenKind::Number);

    auto current = CurrentToken();
    if (current.kind == TokenKind::Colon)
    {
        AdvanceCurrentIndex();
        auto type = (Name*)ParseType();
        return new Number(number, current, type);
    }

    return new Number(number);
}

Block* Parser::ParseFunctionBody()
{
    return ParseBlock(StatementScope::Function);
}

Block* Parser::ParseTypeBody()
{
    return ParseBlock(StatementScope::Type);
}

Block* Parser::ParseMethodBody()
{
    return ParseBlock(StatementScope::Method);
}

Block* Parser::ParseBlock(StatementScope scope)
{
    auto openBracket = AdvanceOnMatch(TokenKind::OpenBracket);
    auto statements = ParseStatements(scope);
    auto closeBracket = AdvanceOnMatch(TokenKind::CloseBracket);

    return new Block(openBracket, statements, closeBracket);
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
        const auto& location = m_tokens.GetSourceLocation(currentToken.locationIndex);
        m_diagnostics.AddError(DiagnosticKind::_0003_ExpectedXButGotY, location);
        return Token::ToError(currentToken);
    }
}

void Parser::SkipUntil(TokenKind kind)
{
    auto currentToken = CurrentToken();
    while (currentToken.kind != kind || currentToken.kind == TokenKind::EndOfFile)
    {
        const auto& location = m_tokens.GetSourceLocation(currentToken.locationIndex);
        m_diagnostics.AddError(DiagnosticKind::Unknown, location);

        AdvanceCurrentIndex();
        currentToken = CurrentToken();
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
