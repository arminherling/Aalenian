#include "Lexer.h"

Lexer::Lexer(const SourceTextSharedPtr& source)
    : source(source)
    , currentIndex(0)
    , currentLine(1)
    , currentColumn(1)
{
}

Token Lexer::NextToken()
{
    while (true)
    {
        auto current = PeekCurrentChar();

        switch (current.unicode())
        {
            case '\r':
            {
                if (PeekNextChar() == '\n')
                    AdvanceCurrentIndex();

                AdvanceCurrentIndexAndResetLine();
                break;
            }
            case '\n':
            {
                AdvanceCurrentIndexAndResetLine();
                break;
            }
            case '\t':
            case ' ':
            {
                AdvanceCurrentIndex();
                break;
            }
            case '+':
                return CreateTokenAndAdvance(TokenKind::Plus, QString("+"));
            case '-':
                return CreateTokenAndAdvance(TokenKind::Minus, QString("-"));
            case '*':
                return CreateTokenAndAdvance(TokenKind::Star, QString("*"));
            case '/':
                return CreateTokenAndAdvance(TokenKind::Slash, QString("/"));
            case '.':
                return CreateTokenAndAdvance(TokenKind::Dot, QString("."));
            case ',':
                return CreateTokenAndAdvance(TokenKind::Comma, QString(","));
            case '=':
                return CreateTokenAndAdvance(TokenKind::Equal, QString("="));
            case '(':
                return CreateTokenAndAdvance(TokenKind::OpenParenthesis, QString("("));
            case ')':
                return CreateTokenAndAdvance(TokenKind::CloseParenthesis, QString(")"));
            case '{':
                return CreateTokenAndAdvance(TokenKind::OpenBracket, QString("{"));
            case '}':
                return CreateTokenAndAdvance(TokenKind::CloseBracket, QString("}"));
            case '\0':
                return CreateTokenAndAdvance(TokenKind::EndOfFile, QString("\0"));
            case '\"':
                return LexString();
            default:
            {
                if (current == '_' || current.isLetter())
                {
                    return LexIdentifier();
                }
                else if (current.isNumber())
                {
                    return LexNumber();
                }

                auto token = CreateTokenAndAdvance(TokenKind::Unknown, current);
                diagnostics.AddError(DiagnosticKind::_0001_FoundIllegalCharacter, token.location);
                return token;
            }
        }
    }
}

LexerResult Lexer::Lex()
{
    QList<Token> tokens;

    while (true)
    {
        auto token = NextToken();
        tokens.append(token);

        if (token.kind == TokenKind::EndOfFile)
            break;
    }

    return LexerResult(diagnostics, tokens);
}

QChar Lexer::PeekCurrentChar()
{
    return PeekChar(0);
}

QChar Lexer::PeekNextChar()
{
    return PeekChar(1);
}

QChar Lexer::PeekChar(int offset)
{
    auto charIndex = currentIndex + offset;
    if (charIndex >= source->text.length())
        return '\0';

    return source->text[charIndex];
}

void Lexer::AdvanceCurrentIndex()
{
    currentIndex++;
    currentColumn++;
}

void Lexer::AdvanceCurrentIndexAndResetLine()
{
    AdvanceCurrentIndex();
    currentLine++;
    currentColumn = 1;
}

Token Lexer::LexIdentifier()
{
    auto startIndex = currentIndex;
    auto startLine = currentLine;
    auto startColumn = currentColumn;
    while (PeekCurrentChar() == '_' || PeekCurrentChar().isLetterOrNumber())
        AdvanceCurrentIndex();

    return CreateLexemeAndToken(TokenKind::Identifier, startIndex, startLine, startColumn);
}

Token Lexer::LexNumber()
{
    auto startIndex = currentIndex;
    auto startLine = currentLine;
    auto startColumn = currentColumn;

    while (PeekCurrentChar().isNumber() || (PeekCurrentChar() == '_' && PeekNextChar() != '.'))
        AdvanceCurrentIndex();

    if (PeekCurrentChar() == '.' && PeekNextChar().isNumber())
    {
        AdvanceCurrentIndex();

        while (PeekCurrentChar().isNumber() || PeekCurrentChar() == '_')
            AdvanceCurrentIndex();
    }

    return CreateLexemeAndToken(TokenKind::Number, startIndex, startLine, startColumn);
}

Token Lexer::LexString()
{
    auto startIndex = currentIndex;
    auto startLine = currentLine;
    auto startColumn = currentColumn;

    // Consume opening quotation mark
    AdvanceCurrentIndex();
    while (PeekCurrentChar() != '\"' && PeekCurrentChar() != '\0')
        AdvanceCurrentIndex();

    if (PeekCurrentChar() == '\"')
    {
        // Consume closing quotation mark
        AdvanceCurrentIndex();

        return CreateLexemeAndToken(TokenKind::String, startIndex, startLine, startColumn);
    }
    else
    {
        auto token = CreateLexemeAndToken(TokenKind::Error, startIndex, startLine, startColumn);
        diagnostics.AddError(DiagnosticKind::_0002_UnterminatedString, token.location);
        return token;
    }
}

Token Lexer::CreateLexemeAndToken(TokenKind kind, int startIndex, int startLine, int startColumn)
{
    auto length = currentIndex - startIndex;
    auto lexeme = source->text.sliced(startIndex, length);
    auto location = SourceLocation(source->text, startIndex, currentIndex - 1);
    return Token(kind, lexeme, location);
}

Token Lexer::CreateTokenAndAdvance(TokenKind kind, const QString& lexeme)
{
    auto start = currentIndex;
    auto lexemeLength = lexeme.length();
    currentIndex += lexemeLength;
    currentColumn += lexemeLength;
    auto location = SourceLocation(source->text, start, currentIndex - 1);
    return Token(kind, lexeme, location);
}
