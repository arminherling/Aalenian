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
                return CreateTokenAndAdvance(TokenKind::Plus, "+");
            case '-':
                return CreateTokenAndAdvance(TokenKind::Minus, "-");
            case '*':
                return CreateTokenAndAdvance(TokenKind::Star, "*");
            case '/':
                return CreateTokenAndAdvance(TokenKind::Slash, "/");
            case '.':
                return CreateTokenAndAdvance(TokenKind::Dot, ".");
            case ',':
                return CreateTokenAndAdvance(TokenKind::Comma, ",");
            case '=':
                return CreateTokenAndAdvance(TokenKind::Equal, "=");
            case '(':
                return CreateTokenAndAdvance(TokenKind::OpenParenthesis, "(");
            case ')':
                return CreateTokenAndAdvance(TokenKind::CloseParenthesis, ")");
            case '{':
                return CreateTokenAndAdvance(TokenKind::OpenBracket, "{");
            case '}':
                return CreateTokenAndAdvance(TokenKind::CloseBracket, "}");
            case '\0':
                return CreateTokenAndAdvance(TokenKind::EndOfFile, "\0");
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
                // TODO diagnostics
                return token;
            }
        }
    }
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
        // TODO diagnostics
        return CreateLexemeAndToken(TokenKind::Error, start);
    }
}

Token Lexer::CreateLexemeAndToken(TokenKind kind, int startIndex)
{
    auto length = currentIndex - startIndex;
    auto lexeme = source.text.sliced(startIndex, length);
    auto location = SourceLocation(source.text, startIndex, currentIndex - 1);
    return Token(kind, lexeme, location);
}

Token Lexer::CreateTokenAndAdvance(TokenKind kind, const QString& lexeme)
{
    auto start = currentIndex;
    currentIndex += lexeme.length();
    auto location = SourceLocation(source.text, start, currentIndex - 1);
    return Token(kind, lexeme, location);
}
