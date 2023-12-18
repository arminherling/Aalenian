#include <Syntax/Parser.h>
#include <Syntax/AssignmentStatement.h>
#include <Syntax/ExpressionStatement.h>
#include <Syntax/FunctionDefinitionStatement.h>
#include <Syntax/EnumDefinitionStatement.h>
#include <Syntax/TypeDefinitionStatement.h>
#include <Syntax/FieldDeclarationStatement.h>
#include <Syntax/MethodDefinitionStatement.h>
#include <Syntax/IfStatement.h>
#include <Syntax/WhileStatement.h>
#include <Syntax/ReturnStatement.h>
#include <Syntax/UnaryExpression.h>
#include <Syntax/BinaryExpression.h>
#include <Syntax/Discard.h>
#include <Syntax/MemberAccess.h>
#include <Syntax/ScopeAccess.h>
#include <Syntax/Error.h>
#include <Syntax/FunctionCall.h>

bool IsFunctionDefinitionKeyword(const QStringView& lexeme)
{
    return lexeme == QString("define");
}

bool IsEnumDefinitionKeyword(const QStringView& lexeme)
{
    return lexeme == QString("enum");
}

bool IsTypeDefinitionKeyword(const QStringView& lexeme)
{
    return lexeme == QString("type");
}

bool IsIfKeyword(const QStringView& lexeme)
{
    return lexeme == QString("if");
}

bool IsWhileKeyword(const QStringView& lexeme)
{
    return lexeme == QString("while");
}

bool IsReturnKeyword(const QStringView& lexeme)
{
    return lexeme == QString("return");
}

bool IsTrueKeyword(const QStringView& lexeme)
{
    return lexeme == QString("true");
}

bool IsFalseKeyword(const QStringView& lexeme)
{
    return lexeme == QString("false");
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
                statements.append(ParseAssignmentStatement());
                break;
            }
            case TokenKind::Dot:
            case TokenKind::Number:
            {
                statements.append(ParseExpressionStatement());
                break;
            }
            case TokenKind::Identifier:
            {
                auto lexeme = m_tokens.GetLexeme(currentToken.kindIndex);
                if (scope == StatementScope::Global)
                {
                    if (IsFunctionDefinitionKeyword(lexeme))
                    {
                        statements.append(ParseFunctionDefinitionStatement());
                        break;
                    }
                    else if (IsTypeDefinitionKeyword(lexeme))
                    {
                        statements.append(ParseTypeDefinitionStatement());
                        break;
                    }
                    else if (IsEnumDefinitionKeyword(lexeme))
                    {
                        statements.append(ParseEnumDefinitionStatement());
                        break;
                    }
                }
                else if (scope == StatementScope::Function || scope == StatementScope::Method)
                {
                    if (IsIfKeyword(lexeme))
                    {
                        statements.append(ParseIfStatement(scope));
                        break;
                    }
                    else if (IsWhileKeyword(lexeme))
                    {
                        statements.append(ParseWhileStatement(scope));
                        break;
                    }
                    else if (IsReturnKeyword(lexeme))
                    {
                        statements.append(ParseReturnStatement());
                        break;
                    }
                }
                else if (scope == StatementScope::Type)
                {
                    if (IsFunctionDefinitionKeyword(lexeme))
                    {
                        statements.append(ParseMethodDefinitionStatement());
                        break;
                    }

                    statements.append(ParseFieldDeclarationStatement());
                    break;
                }
                else if (scope == StatementScope::Enum)
                {
                    statements.append(ParseEnumMember());
                    break;
                }

                auto nextToken = NextToken();
                if (nextToken.kind == TokenKind::Equal)
                {
                    statements.append(ParseAssignmentStatement());
                }
                else if (nextToken.kind == TokenKind::OpenParenthesis)
                {
                    auto expressionStatement = ParseExpressionStatement();
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

Statement* Parser::ParseAssignmentStatement()
{
    auto leftExpression = ParsePrimaryExpression();
    auto equals = AdvanceOnMatch(TokenKind::Equal);
    auto rightExpression = ParseExpression();
    return new AssignmentStatement(leftExpression, equals, rightExpression);
}

Statement* Parser::ParseExpressionStatement()
{
    auto expression = ParseExpression();
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

Statement* Parser::ParseEnumDefinitionStatement()
{
    auto keyword = AdvanceOnMatch(TokenKind::Identifier);
    auto name = AdvanceOnMatch(TokenKind::Identifier);

    auto current = CurrentToken();
    std::optional<Type> baseType;
    if (current.kind == TokenKind::Colon)
    {
        AdvanceCurrentIndex();
        baseType = ParseType();
        current = CurrentToken();
    }

    auto body = ParseEnumBody();

    return new EnumDefinitionStatement(keyword, name, baseType, body);
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
    auto name = ParseName();
    auto current = CurrentToken();
    std::optional<Token> colon;
    std::optional<Type> type;
    if (current.kind == TokenKind::Colon)
    {
        AdvanceCurrentIndex();
        colon = current;
        type = ParseType();
        current = CurrentToken();
    }

    std::optional<Token> equals;
    std::optional<Expression*> expression;
    if (current.kind == TokenKind::Equal)
    {
        equals = current;
        AdvanceCurrentIndex();
        expression = ParseExpression();
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

Statement* Parser::ParseIfStatement(StatementScope scope)
{
    auto keyword = AdvanceOnMatch(TokenKind::Identifier);
    auto condition = ParseExpression();
    auto block = ParseBlock(scope);

    return new IfStatement(keyword, condition, block);
}

Statement* Parser::ParseWhileStatement(StatementScope scope)
{
    auto keyword = AdvanceOnMatch(TokenKind::Identifier);
    auto condition = ParseExpression();
    auto block = ParseBlock(scope);

    return new WhileStatement(keyword, condition, block);
}

Statement* Parser::ParseReturnStatement()
{
    auto keyword = AdvanceOnMatch(TokenKind::Identifier);

    std::optional<Expression*> expression;
    // Special case: we need to disambiguate between returns in void functions and normal functions
    // we do this by breaking the code up with a line break
    if(HasPossibleReturnValue(keyword))
        expression = ParseExpression();
    
    return new ReturnStatement(keyword, expression);
}

Parameters* Parser::ParseParameters()
{
    auto openParenthesis = AdvanceOnMatch(TokenKind::OpenParenthesis);
    auto currentToken = CurrentToken();

    QList<Parameter*> parameters;
    while (currentToken.kind != TokenKind::CloseParenthesis)
    {
        parameters.append(ParseParameter());
        if (CurrentToken().kind == TokenKind::Comma)
        {
            AdvanceCurrentIndex();

            // if(CurrentToken().kind == TokenKind::CloseParenthesis)
            // Too many commas or too few parameters
        }
        currentToken = CurrentToken();
    }

    auto closeParenthesis = AdvanceOnMatch(TokenKind::CloseParenthesis);
    return new Parameters(openParenthesis, parameters, closeParenthesis);
}

Expression* Parser::ParseExpression()
{
    return ParseBinaryExpression(0);
}

Expression* Parser::ParseBinaryExpression(i32 parentPrecedence)
{
    Expression* left = nullptr;
    auto unaryOperator = CurrentToken();

    auto unaryPrecedence = UnaryOperatorPrecedence(unaryOperator.kind);
    if (unaryPrecedence == 0 || unaryPrecedence < parentPrecedence)
    {
        left = ParsePrimaryExpression();
    }
    else
    {
        AdvanceCurrentIndex();
        auto expression = ParseBinaryExpression(unaryPrecedence);
        left = new UnaryExpression(unaryOperator, expression);
    }

    while (true)
    {
        auto binaryOperator = CurrentToken();
        if (binaryOperator.kind == TokenKind::EndOfFile)
            break;

        auto binaryPrecedence = BinaryOperatorPrecedence(binaryOperator.kind);
        if (binaryPrecedence == 0 || binaryPrecedence <= parentPrecedence)
            break;

        // Special case: empty lines prevent unintended method chaining
        if (HasLineBreakSinceLastMemberAccess())
            break;

        AdvanceCurrentIndex();
        auto right = ParseBinaryExpression(binaryPrecedence);
        left = new BinaryExpression(left, binaryOperator, right);
    }

    return left;
}

Expression* Parser::ParsePrimaryExpression()
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
            auto maybeBool = TryParseBool();
            if (maybeBool.has_value())
                return maybeBool.value();

            return ParseFunctionCallOrName();
        }
        case TokenKind::Number:
        {
            return ParseNumberLiteral();
        }
        case TokenKind::OpenParenthesis:
        {
            return ParseGrouping();
        }
        case TokenKind::Dot:
        {
            AdvanceCurrentIndex();
            auto expression = ParseFunctionCallOrName();
            return new MemberAccess(currentToken, expression);
        }
        case TokenKind::DoubleColon:
        {
            AdvanceCurrentIndex();
            auto expression = ParseFunctionCallOrName();
            return new ScopeAccess(currentToken, expression);
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
    auto currentToken = CurrentToken();

    QList<Argument*> arguments;
    while (currentToken.kind != TokenKind::CloseParenthesis)
    {
        arguments.append(ParseArgument());
        if (CurrentToken().kind == TokenKind::Comma)
        {
            AdvanceCurrentIndex();

            // if(CurrentToken().kind == TokenKind::CloseParenthesis)
            // Too many commas or too few arguments
        }
        currentToken = CurrentToken();
    }

    auto closeParenthesis = AdvanceOnMatch(TokenKind::CloseParenthesis);
    return new Arguments(openParenthesis, arguments, closeParenthesis);
}

Type Parser::ParseType()
{
    auto ref = TryMatchKeyword(QString("ref"));
    auto name = ParseName();
    return Type(ref, name);
}

Name* Parser::ParseName()
{
    auto name = AdvanceOnMatch(TokenKind::Identifier);
    return new Name(name);
}

Number* Parser::ParseNumberLiteral()
{
    auto number = AdvanceOnMatch(TokenKind::Number);

    auto current = CurrentToken();
    if (current.kind == TokenKind::Colon)
    {
        AdvanceCurrentIndex();
        auto type = ParseType();
        return new Number(number, current, type);
    }

    return new Number(number);
}

Grouping* Parser::ParseGrouping()
{
    auto openParenthesis = AdvanceOnMatch(TokenKind::OpenParenthesis);
    auto expression = ParseExpression();
    auto closeParenthesis = AdvanceOnMatch(TokenKind::CloseParenthesis);

    return new Grouping(openParenthesis, expression, closeParenthesis);
}

EnumMember* Parser::ParseEnumMember()
{
    auto memberName = ParseName();

    auto current = CurrentToken();
    if (current.kind == TokenKind::Equal)
    {
        AdvanceCurrentIndex();
        auto value = ParseNumberLiteral();
        return new EnumMember(memberName, current, value);
    }

    return new EnumMember(memberName);
}

Block* Parser::ParseFunctionBody()
{
    return ParseBlock(StatementScope::Function);
}

Block* Parser::ParseEnumBody()
{
    return ParseBlock(StatementScope::Enum);
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

Parameter* Parser::ParseParameter()
{
    auto name = ParseName();
    auto colon = AdvanceOnMatch(TokenKind::Colon);
    auto type = ParseType();

    return new Parameter(name, colon, type);
}

Argument* Parser::ParseArgument()
{
    auto ref = TryMatchKeyword(QString("ref"));
    auto expression = ParseExpression();

    return new Argument(ref, expression);
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

std::optional<Bool*> Parser::TryParseBool()
{
    auto currentToken = CurrentToken();
    auto lexeme = m_tokens.GetLexeme(currentToken.kindIndex);
    if (IsTrueKeyword(lexeme))
    {
        AdvanceCurrentIndex();
        return new Bool(true);
    }
    else if (IsFalseKeyword(lexeme))
    {
        AdvanceCurrentIndex();
        return new Bool(false);
    }
    return {};
}

std::optional<Token> Parser::TryMatchKeyword(const QStringView& keyword)
{
    auto currentToken = CurrentToken();
    if (currentToken.kind == TokenKind::Identifier 
        && m_tokens.GetLexeme(currentToken.kindIndex) == keyword)
    {
        AdvanceCurrentIndex();
        return currentToken;
    }

    return std::optional<Token>();
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

Token Parser::Peek(i32 offset)
{
    auto index = m_currentIndex + offset;
    if (index >= m_tokens.size())
        return Token{ .kind = TokenKind::EndOfFile };

    return m_tokens[index];
}

bool Parser::HasLineBreakSinceLastMemberAccess()
{
    auto currentToken = CurrentToken();
    if (currentToken.kind != TokenKind::Dot)
        return false;

    auto lastToken = Peek(-1);
    auto lastTokenLocation = m_tokens.GetSourceLocation(lastToken.locationIndex);
    auto currentTokenLocation = m_tokens.GetSourceLocation(currentToken.locationIndex);

    auto hasEmptyLineBreak = (currentTokenLocation.endLine - lastTokenLocation.endLine) >= 2;
    return hasEmptyLineBreak;
}

bool Parser::HasPossibleReturnValue(const Token& returnKeyword)
{
    auto currentToken = CurrentToken();
    if (currentToken.kind == TokenKind::CloseBracket)
        return false;

    auto returnTokenLocation = m_tokens.GetSourceLocation(returnKeyword.locationIndex);
    auto currentTokenLocation = m_tokens.GetSourceLocation(currentToken.locationIndex);

    auto isOnSameLine = returnTokenLocation.endLine == currentTokenLocation.endLine;
    return isOnSameLine;
}

COMPILER_API ParseTree Parse(const TokenBuffer& tokens, DiagnosticsBag& diagnostics) noexcept
{
    Parser parser{ tokens, diagnostics };
    return parser.Parse();
}
