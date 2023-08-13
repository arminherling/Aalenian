#include "Lexer.h"

Lexer::Lexer(const SourceText& source)
    : source(source)
    , currentIndex(0)
    , lineNumber(0)
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
                return CreateTokenAndAdvance(TokenKind::Plus, '+');
            case '-':
                return CreateTokenAndAdvance(TokenKind::Minus, '-');
            case '*':
                return CreateTokenAndAdvance(TokenKind::Star, '*');
            case '/':
                return CreateTokenAndAdvance(TokenKind::Slash, '/');
            case '.':
                return CreateTokenAndAdvance(TokenKind::Dot, '.');
            case ',':
                return CreateTokenAndAdvance(TokenKind::Comma, ',');
            case '=':
                return CreateTokenAndAdvance(TokenKind::Equal, '=');
            case '(':
                return CreateTokenAndAdvance(TokenKind::OpenParenthesis, '(');
            case ')':
                return CreateTokenAndAdvance(TokenKind::CloseParenthesis, ')');
            case '{':
                return CreateTokenAndAdvance(TokenKind::OpenBracket, '{');
            case '}':
                return CreateTokenAndAdvance(TokenKind::CloseBracket, '}');
            case '\0':
                return CreateTokenAndAdvance(TokenKind::EndOfFile, '\0');
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
    if (charIndex >= source.text.length())
        return '\0';

    return source.text[charIndex];
}

void Lexer::AdvanceCurrentIndex()
{
    currentIndex++;
}

void Lexer::AdvanceCurrentIndexAndResetLine()
{
    AdvanceCurrentIndex();
    lineNumber++;
}

Token Lexer::LexIdentifier()
{
    auto start = currentIndex;
    while (PeekCurrentChar() == '_' || PeekCurrentChar().isLetterOrNumber())
        AdvanceCurrentIndex();

    return CreateLexemeAndToken(TokenKind::Identifier, start);
}

Token Lexer::LexNumber()
{
    auto start = currentIndex;

    while (PeekCurrentChar().isNumber() || (PeekCurrentChar() == '_' && PeekNextChar() != '.'))
        AdvanceCurrentIndex();

    if (PeekCurrentChar() == '.' && PeekNextChar().isNumber())
    {
        AdvanceCurrentIndex();

        while (PeekCurrentChar().isNumber() || PeekCurrentChar() == '_')
            AdvanceCurrentIndex();
    }

    return CreateLexemeAndToken(TokenKind::Number, start);
}

Token Lexer::LexString()
{
    auto start = currentIndex;

    // Consume opening quotation mark
    AdvanceCurrentIndex();
    while (PeekCurrentChar() != '\"' && PeekCurrentChar() != '\0')
        AdvanceCurrentIndex();

    if (PeekCurrentChar() == '\"')
    {
        // Consume closing quotation mark
        AdvanceCurrentIndex();

        return CreateLexemeAndToken(TokenKind::String, start);
    }
    else
    {
        auto token = CreateLexemeAndToken(TokenKind::Error, start);
        diagnostics.AddError(DiagnosticKind::_0002_UnterminatedString, token.location);
        return token;
    }
}

Token Lexer::CreateLexemeAndToken(TokenKind kind, int startIndex)
{
    auto length = currentIndex - startIndex;
    auto lexeme = source.text.sliced(startIndex, length);
    auto location = SourceLocation(source.text, startIndex, currentIndex - 1);
    return Token(kind, lexeme, location);
}

Token Lexer::CreateTokenAndAdvance(TokenKind kind, const QChar& c)
{
    auto start = currentIndex;
    currentIndex++;
    auto location = SourceLocation(source.text, start, currentIndex - 1);
    return Token(kind, c, location);
}
