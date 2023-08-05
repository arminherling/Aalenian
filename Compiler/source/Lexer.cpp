#include "Lexer.h"

Lexer::Lexer(const SourceText& source)
    : m_source(source)
    , m_index(0)
{
}

Token Lexer::NextToken()
{
    while (true)
    {
        auto current = PeekCurrentChar();

        switch (current.unicode())
        {
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
            default:
            {
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
    auto index = m_index + offset;
    if (index >= m_source.text.length())
        return '\0';

    return m_source.text[index];
}

Token Lexer::CreateTokenAndAdvance(TokenKind kind, const QString& lexeme)
{
    m_index += lexeme.length();
    
    return Token(kind, lexeme);
}
