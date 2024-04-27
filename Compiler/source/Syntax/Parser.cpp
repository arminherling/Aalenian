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
#include <Syntax/DiscardLiteral.h>
#include <Syntax/MemberAccessExpression.h>
#include <Syntax/ScopeAccessExpression.h>
#include <Syntax/Error.h>
#include <Syntax/FunctionCallExpression.h>

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

bool IsRefKeyword(const QStringView& lexeme)
{
    return lexeme == QString("ref");
}

Parser::Parser(const TokenBuffer& tokens, DiagnosticsBag& diagnostics)
    : m_tokens{ tokens }
    , m_diagnostics{ diagnostics }
    , m_currentIndex{ 0 }
{
}

ParseTree Parser::parse()
{
    auto globalStatements = parseGlobalStatements();

    return ParseTree(m_tokens, globalStatements);
}

QList<Statement*> Parser::parseGlobalStatements()
{
    return parseStatements(StatementScope::Global);
}

QList<Statement*> Parser::parseStatements(StatementScope scope)
{
    QList<Statement*> statements;

    auto current = currentToken();
    while (true)
    {
        switch (current.kind)
        {
            case TokenKind::Underscore:
            {
                statements.append(parseAssignmentStatement());
                break;
            }
            case TokenKind::Dot:
            case TokenKind::Number:
            {
                statements.append(parseExpressionStatement());
                break;
            }
            case TokenKind::Identifier:
            {
                auto& lexeme = m_tokens.getLexeme(current);
                if (scope == StatementScope::Global)
                {
                    if (IsFunctionDefinitionKeyword(lexeme))
                    {
                        statements.append(parseFunctionDefinitionStatement());
                        break;
                    }
                    else if (IsTypeDefinitionKeyword(lexeme))
                    {
                        statements.append(parseTypeDefinitionStatement());
                        break;
                    }
                    else if (IsEnumDefinitionKeyword(lexeme))
                    {
                        statements.append(parseEnumDefinitionStatement());
                        break;
                    }
                }
                else if (scope == StatementScope::Function || scope == StatementScope::Method)
                {
                    if (IsIfKeyword(lexeme))
                    {
                        statements.append(parseIfStatement(scope));
                        break;
                    }
                    else if (IsWhileKeyword(lexeme))
                    {
                        statements.append(parseWhileStatement(scope));
                        break;
                    }
                    else if (IsReturnKeyword(lexeme))
                    {
                        statements.append(parseReturnStatement());
                        break;
                    }
                }
                else if (scope == StatementScope::Type)
                {
                    if (IsFunctionDefinitionKeyword(lexeme))
                    {
                        statements.append(parseMethodDefinitionStatement());
                        break;
                    }

                    statements.append(parseFieldDeclarationStatement());
                    break;
                }

                auto next = nextToken();
                if (next.kind == TokenKind::Equal)
                {
                    statements.append(parseAssignmentStatement());
                }
                else if (next.kind == TokenKind::OpenParenthesis)
                {
                    auto expressionStatement = parseExpressionStatement();
                    statements.append(expressionStatement);
                }
                else
                {
                    const auto& location = m_tokens.getSourceLocation(current);
                    m_diagnostics.AddError(DiagnosticKind::Unknown, location);

                    advanceCurrentIndex();
                }
                break;
            }
            case TokenKind::CloseBracket:
            {
                if (scope == StatementScope::Global)
                {
                    const auto& location = m_tokens.getSourceLocation(current);
                    m_diagnostics.AddError(DiagnosticKind::Unknown, location);

                    advanceCurrentIndex();
                    break;
                }
            }
            case TokenKind::EndOfFile:
            {
                return statements;
            }
            default:
            {
                const auto& location = m_tokens.getSourceLocation(current);
                m_diagnostics.AddError(DiagnosticKind::Unknown, location);

                advanceCurrentIndex();
                break;
            }
        }

        current = currentToken();
    }
}

Statement* Parser::parseAssignmentStatement()
{
    auto leftExpression = parsePrimaryExpression();
    auto equals = advanceOnMatch(TokenKind::Equal);
    auto rightExpression = parseExpression();
    return new AssignmentStatement(leftExpression, equals, rightExpression);
}

Statement* Parser::parseExpressionStatement()
{
    auto expression = parseExpression();
    return new ExpressionStatement(expression);
}

Statement* Parser::parseFunctionDefinitionStatement()
{
    auto keyword = advanceOnMatch(TokenKind::Identifier);
    auto name = advanceOnMatch(TokenKind::Identifier);
    auto signature = parseParametersNode();
    auto body = parseFunctionBody();

    return new FunctionDefinitionStatement(keyword, name, signature, body);
}

Statement* Parser::parseEnumDefinitionStatement()
{
    auto keyword = advanceOnMatch(TokenKind::Identifier);
    auto name = advanceOnMatch(TokenKind::Identifier);

    auto current = currentToken();
    std::optional<TypeName> baseType;
    if (current.kind == TokenKind::Colon)
    {
        advanceCurrentIndex();
        baseType = parseTypeNode();
        current = currentToken();
    }

    auto openBracket = advanceOnMatch(TokenKind::OpenBracket);
    auto fieldDefinitions = parseEnumFieldDefinitions();
    auto closeBracket = advanceOnMatch(TokenKind::CloseBracket);

    return new EnumDefinitionStatement(keyword, name, baseType, openBracket, fieldDefinitions, closeBracket);
}

QList<EnumFieldDefinitionStatement*> Parser::parseEnumFieldDefinitions()
{
    QList<EnumFieldDefinitionStatement*> definitions;

    auto current = currentToken();
    while (true)
    {
        switch (current.kind)
        {
            case TokenKind::Identifier:
            {
                definitions.append(parseEnumFieldDefinitionStatement());
                break;
            }
            case TokenKind::CloseBracket:
            case TokenKind::EndOfFile:
            {
                return definitions;
            }
            default:
            {
                const auto& location = m_tokens.getSourceLocation(current);
                m_diagnostics.AddError(DiagnosticKind::Unknown, location);

                advanceCurrentIndex();
                break;
            }
        }

        current = currentToken();
    }

    return definitions;
}

Statement* Parser::parseTypeDefinitionStatement()
{
    auto keyword = advanceOnMatch(TokenKind::Identifier);
    auto name = advanceOnMatch(TokenKind::Identifier);
    auto body = parseTypeBody();

    return new TypeDefinitionStatement(keyword, name, body);
}

Statement* Parser::parseFieldDeclarationStatement()
{
    auto name = parseNameExpression();
    auto current = currentToken();
    std::optional<Token> colon;
    std::optional<TypeName> type;
    if (current.kind == TokenKind::Colon)
    {
        advanceCurrentIndex();
        colon = current;
        type = parseTypeNode();
        current = currentToken();
    }

    std::optional<Token> equals;
    std::optional<Expression*> expression;
    if (current.kind == TokenKind::Equal)
    {
        equals = current;
        advanceCurrentIndex();
        expression = parseExpression();
    }

    return new FieldDeclarationStatement(name, colon, type, equals, expression);
}

Statement* Parser::parseMethodDefinitionStatement()
{
    auto keyword = advanceOnMatch(TokenKind::Identifier);
    auto name = advanceOnMatch(TokenKind::Identifier);
    auto signature = parseParametersNode();
    auto body = parseMethodBody();

    return new MethodDefinitionStatement(keyword, name, signature, body);
}

Statement* Parser::parseIfStatement(StatementScope scope)
{
    auto keyword = advanceOnMatch(TokenKind::Identifier);
    auto condition = parseExpression();
    auto block = parseBlockNode(scope);

    return new IfStatement(keyword, condition, block);
}

Statement* Parser::parseWhileStatement(StatementScope scope)
{
    auto keyword = advanceOnMatch(TokenKind::Identifier);
    auto condition = parseExpression();
    auto block = parseBlockNode(scope);

    return new WhileStatement(keyword, condition, block);
}

Statement* Parser::parseReturnStatement()
{
    auto keyword = advanceOnMatch(TokenKind::Identifier);

    std::optional<Expression*> expression;
    // Special case: we need to disambiguate between returns in void functions and normal functions
    // we do this by breaking the code up with a line break
    if (hasPossibleReturnValue(keyword))
        expression = parseExpression();

    return new ReturnStatement(keyword, expression);
}

ParametersNode* Parser::parseParametersNode()
{
    auto openParenthesis = advanceOnMatch(TokenKind::OpenParenthesis);
    auto current = currentToken();

    QList<ParameterNode*> parameters;
    while (current.kind != TokenKind::CloseParenthesis)
    {
        parameters.append(parseParameterNode());
        if (currentToken().kind == TokenKind::Comma)
        {
            advanceCurrentIndex();

            // if(CurrentToken().kind == TokenKind::CloseParenthesis)
            // Too many commas or too few parameters
        }
        current = currentToken();
    }

    auto closeParenthesis = advanceOnMatch(TokenKind::CloseParenthesis);
    return new ParametersNode(openParenthesis, parameters, closeParenthesis);
}

Expression* Parser::parseExpression()
{
    return parseBinaryExpression(0);
}

Expression* Parser::parseBinaryExpression(i32 parentPrecedence)
{
    Expression* left = nullptr;
    auto unaryOperatorToken = currentToken();

    auto unaryPrecedence = unaryOperatorPrecedence(unaryOperatorToken);
    if (unaryPrecedence == 0 || unaryPrecedence < parentPrecedence)
    {
        left = parsePrimaryExpression();
    }
    else
    {
        advanceCurrentIndex();
        auto unaryOperator = convertUnaryOperatorTokenKindToEnum(unaryOperatorToken);
        auto expression = parseBinaryExpression(unaryPrecedence);
        left = new UnaryExpression(unaryOperatorToken, unaryOperator, expression);
    }

    while (true)
    {
        auto binaryOperatorToken = currentToken();
        if (binaryOperatorToken.kind == TokenKind::EndOfFile)
            break;

        auto binaryPrecedence = binaryOperatorPrecedence(binaryOperatorToken.kind);
        if (binaryPrecedence == 0 || binaryPrecedence <= parentPrecedence)
            break;

        // Special case: empty lines prevent unintended method chaining
        if (hasLineBreakSinceLastMemberAccess())
            break;

        advanceCurrentIndex();
        auto binaryOperator = convertBinaryOperatorTokenKindToEnum(binaryOperatorToken.kind);
        auto right = parseBinaryExpression(binaryPrecedence);
        left = new BinaryExpression(left, binaryOperatorToken, binaryOperator, right);
    }

    return left;
}

Expression* Parser::parsePrimaryExpression()
{
    auto current = currentToken();

    switch (current.kind)
    {
        case TokenKind::Underscore:
        {
            advanceCurrentIndex();
            return new DiscardLiteral(current);
        }
        case TokenKind::Identifier:
        {
            auto maybeBool = tryParseBoolLiteral();
            if (maybeBool.has_value())
                return maybeBool.value();

            return parseFunctionCallOrNameExpression();
        }
        case TokenKind::Number:
        {
            return parseNumberLiteral();
        }
        case TokenKind::OpenParenthesis:
        {
            return parseGroupingExpression();
        }
        case TokenKind::Dot:
        {
            advanceCurrentIndex();
            auto expression = parseFunctionCallOrNameExpression();
            return new MemberAccessExpression(current, expression);
        }
        case TokenKind::DoubleColon:
        {
            advanceCurrentIndex();
            auto expression = parseFunctionCallOrNameExpression();
            return new ScopeAccessExpression(current, expression);
        }
        default:
        {
            const auto& location = m_tokens.getSourceLocation(current);
            m_diagnostics.AddError(DiagnosticKind::Unknown, location);

            advanceCurrentIndex();
            return new Error(current);
        }
    }
}

Expression* Parser::parseFunctionCallOrNameExpression()
{
    auto next = nextToken();
    if (next.kind == TokenKind::OpenParenthesis)
    {
        return parseFunctionCallExpression();
    }
    else
    {
        return parseNameExpression();
    }
}

Expression* Parser::parseFunctionCallExpression()
{
    auto name = advanceOnMatch(TokenKind::Identifier);
    auto arguments = parseArgumentsNode();
    return new FunctionCallExpression(name, arguments);
}

ArgumentsNode* Parser::parseArgumentsNode()
{
    auto openParenthesis = advanceOnMatch(TokenKind::OpenParenthesis);
    auto current = currentToken();

    QList<ArgumentNode*> arguments;
    while (current.kind != TokenKind::CloseParenthesis)
    {
        arguments.append(parseArgumentNode());
        if (currentToken().kind == TokenKind::Comma)
        {
            advanceCurrentIndex();

            // if(CurrentToken().kind == TokenKind::CloseParenthesis)
            // TODO print error for too many commas or too few arguments
        }
        current = currentToken();
    }

    auto closeParenthesis = advanceOnMatch(TokenKind::CloseParenthesis);
    return new ArgumentsNode(openParenthesis, arguments, closeParenthesis);
}

TypeName Parser::parseTypeNode()
{
    // TODO ref should probably be an unary operator?
    auto ref = tryMatchKeyword(QString("ref"));
    auto name = parseNameExpression();
    return TypeName(ref, name);
}

NameExpression* Parser::parseNameExpression()
{
    auto name = advanceOnMatch(TokenKind::Identifier);
    return new NameExpression(name);
}

NumberLiteral* Parser::parseNumberLiteral()
{
    auto number = advanceOnMatch(TokenKind::Number);

    auto current = currentToken();
    if (current.kind == TokenKind::Colon)
    {
        advanceCurrentIndex();
        auto type = parseTypeNode();
        // TODO add diagnostic for invalid type
        return new NumberLiteral(number, current, type);
    }

    return new NumberLiteral(number);
}

GroupingExpression* Parser::parseGroupingExpression()
{
    auto openParenthesis = advanceOnMatch(TokenKind::OpenParenthesis);
    auto expression = parseExpression();
    auto closeParenthesis = advanceOnMatch(TokenKind::CloseParenthesis);

    return new GroupingExpression(openParenthesis, expression, closeParenthesis);
}

EnumFieldDefinitionStatement* Parser::parseEnumFieldDefinitionStatement()
{
    auto memberName = parseNameExpression();

    auto current = currentToken();
    if (current.kind == TokenKind::Equal)
    {
        advanceCurrentIndex();
        auto value = parseNumberLiteral();
        return new EnumFieldDefinitionStatement(memberName, current, value);
    }

    return new EnumFieldDefinitionStatement(memberName);
}

BlockNode* Parser::parseFunctionBody()
{
    return parseBlockNode(StatementScope::Function);
}

BlockNode* Parser::parseTypeBody()
{
    return parseBlockNode(StatementScope::Type);
}

BlockNode* Parser::parseMethodBody()
{
    return parseBlockNode(StatementScope::Method);
}

BlockNode* Parser::parseBlockNode(StatementScope scope)
{
    auto openBracket = advanceOnMatch(TokenKind::OpenBracket);
    auto statements = parseStatements(scope);
    auto closeBracket = advanceOnMatch(TokenKind::CloseBracket);

    return new BlockNode(openBracket, statements, closeBracket);
}

ParameterNode* Parser::parseParameterNode()
{
    auto name = parseNameExpression();
    auto colon = advanceOnMatch(TokenKind::Colon);
    auto type = parseTypeNode();

    return new ParameterNode(name, colon, type);
}

ArgumentNode* Parser::parseArgumentNode()
{
    auto ref = tryMatchKeyword(QString("ref"));
    auto expression = parseExpression();

    return new ArgumentNode(ref, expression);
}

Token Parser::advanceOnMatch(TokenKind kind)
{
    auto current = currentToken();
    if (current.kind == kind)
    {
        advanceCurrentIndex();
        return current;
    }
    else
    {
        const auto& location = m_tokens.getSourceLocation(current);
        m_diagnostics.AddError(DiagnosticKind::_0003_ExpectedXButGotY, location);
        return Token::ToError(current);
    }
}

std::optional<BoolLiteral*> Parser::tryParseBoolLiteral()
{
    auto current = currentToken();
    auto lexeme = m_tokens.getLexeme(current);
    if (IsTrueKeyword(lexeme))
    {
        advanceCurrentIndex();
        return new BoolLiteral(true);
    }
    else if (IsFalseKeyword(lexeme))
    {
        advanceCurrentIndex();
        return new BoolLiteral(false);
    }
    return {};
}

std::optional<Token> Parser::tryMatchKeyword(const QStringView& keyword)
{
    auto current = currentToken();
    if (current.kind == TokenKind::Identifier
        && m_tokens.getLexeme(current) == keyword)
    {
        advanceCurrentIndex();
        return current;
    }

    return std::optional<Token>();
}

void Parser::skipUntil(TokenKind kind)
{
    auto current = currentToken();
    while (current.kind != kind || current.kind == TokenKind::EndOfFile)
    {
        const auto& location = m_tokens.getSourceLocation(current);
        m_diagnostics.AddError(DiagnosticKind::Unknown, location);

        advanceCurrentIndex();
        current = currentToken();
    }
}

Token Parser::peek(i32 offset)
{
    auto index = m_currentIndex + offset;
    if (index >= m_tokens.size())
        return Token{ .kind = TokenKind::EndOfFile };

    return m_tokens[index];
}

bool Parser::hasLineBreakSinceLastMemberAccess()
{
    auto current = currentToken();
    if (current.kind != TokenKind::Dot)
        return false;

    auto lastToken = peek(-1);
    auto lastTokenLocation = m_tokens.getSourceLocation(lastToken);
    auto currentTokenLocation = m_tokens.getSourceLocation(current);

    auto hasEmptyLineBreak = (currentTokenLocation.endLine - lastTokenLocation.endLine) >= 2;
    return hasEmptyLineBreak;
}

bool Parser::hasPossibleReturnValue(const Token& returnKeyword)
{
    auto current = currentToken();
    if (current.kind == TokenKind::CloseBracket)
        return false;

    auto returnTokenLocation = m_tokens.getSourceLocation(returnKeyword);
    auto currentTokenLocation = m_tokens.getSourceLocation(current);

    auto isOnSameLine = returnTokenLocation.endLine == currentTokenLocation.endLine;
    return isOnSameLine;
}

BinaryOperatornKind Parser::convertBinaryOperatorTokenKindToEnum(TokenKind kind) const
{
    switch (kind)
    {
        case TokenKind::DoubleColon:
            return BinaryOperatornKind::ScopeAccess;
        case TokenKind::Dot:
            return BinaryOperatornKind::MemberAccess;
        case TokenKind::Plus:
            return BinaryOperatornKind::Addition;
        case TokenKind::Minus:
            return BinaryOperatornKind::Subtraction;
        case TokenKind::Star:
            return BinaryOperatornKind::Multiplication;
        case TokenKind::Slash:
            return BinaryOperatornKind::Division;
        default:
            return BinaryOperatornKind::Invalid;
    }
}

UnaryOperatornKind Parser::convertUnaryOperatorTokenKindToEnum(Token token) const
{
    auto kind = token.kind;
    if (kind == TokenKind::Identifier && IsRefKeyword(m_tokens.getLexeme(token)))
        return UnaryOperatornKind::ReferenceOf;

    if (kind == TokenKind::Minus)
        return UnaryOperatornKind::Negation;

    return UnaryOperatornKind::Invalid;
}

i32 Parser::unaryOperatorPrecedence(Token token) const
{
    auto kind = token.kind;
    if (kind == TokenKind::Identifier && IsRefKeyword(m_tokens.getLexeme(token)))
        return 5;

    if (kind == TokenKind::Minus)
        return 4;

    return 0;
}

i32 Parser::binaryOperatorPrecedence(TokenKind kind) const
{
    switch (kind)
    {
        case TokenKind::Dot:
        case TokenKind::DoubleColon:
            return 3;
        case TokenKind::Star:
        case TokenKind::Slash:
            return 2;
        case TokenKind::Plus:
        case TokenKind::Minus:
            return 1;
    }

    return 0;
}

ParseTree Parse(const TokenBuffer& tokens, DiagnosticsBag& diagnostics) noexcept
{
    Parser parser{ tokens, diagnostics };
    return parser.parse();
}
