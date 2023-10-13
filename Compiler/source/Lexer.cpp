#include "Lexer.h"

#include <unordered_map>

[[nodiscard]] auto InitializeTokenSizes() noexcept
{
    return std::unordered_map<TokenKind, int>{
        {TokenKind::Plus, 1},
        {TokenKind::Minus, 1},
        {TokenKind::Star, 1},
        {TokenKind::Slash, 1},
        {TokenKind::Dot, 1},
        {TokenKind::Comma, 1},
        {TokenKind::Equal, 1},
        {TokenKind::OpenParenthesis, 1},
        {TokenKind::CloseParenthesis, 1},
        {TokenKind::OpenBracket, 1},
        {TokenKind::CloseBracket, 1},
        {TokenKind::EndOfFile, 0},
    };
}

[[nodiscard]] auto TokenSize(TokenKind kind) noexcept
{
    static const auto tokenSizes = InitializeTokenSizes();
    if (auto result = tokenSizes.find(kind); result != tokenSizes.end())
        return result->second;

    return 0;
}

[[nodiscard]] auto PeekChar(const SourceTextSharedPtr& source, int& currentIndex, int offset) noexcept
{
    auto charIndex = currentIndex + offset;
    if (charIndex >= source->text.length())
        return QChar('\0');

    return source->text[charIndex];
};

[[nodiscard]] auto IsNumberOrUnderscore(const QChar& c) noexcept
{
    return c.isNumber() || c == QChar('_');
}

[[nodiscard]] auto IsLetterOrUnderscore(const QChar& c) noexcept
{
    return c.isLetter() || c == QChar('_');
}

[[nodiscard]] auto IsLetterOrNumberOrUnderscore(const QChar& c) noexcept
{
    return c.isLetterOrNumber() || c == QChar('_');
}

[[nodiscard]] auto PeekCurrentChar(const SourceTextSharedPtr& source, int& currentIndex) noexcept { return PeekChar(source, currentIndex, 0); };
[[nodiscard]] auto PeekNextChar(const SourceTextSharedPtr& source, int& currentIndex) noexcept { return PeekChar(source, currentIndex, 1); };

auto AdvanceCurrentIndex(int& currentIndex, int& currentColumn) noexcept
{
    currentIndex++;
    currentColumn++;
};

auto AdvanceCurrentIndexAndResetLine(int& currentIndex, int& currentLine, int& currentColumn) noexcept
{
    currentIndex++;
    currentLine++;
    currentColumn = 1;
};

auto AddTokenKindAndAdvance(TokenBuffer& tokenBuffer, const SourceTextSharedPtr& source, int& currentLine, int& currentIndex, int& currentColumn, TokenKind tokenKind) noexcept
{
    auto tokenSize = TokenSize(tokenKind);
    auto locationIndex = tokenBuffer.AddSourceLocation(
        {
            .source = source,
            .startIndex = currentIndex,
            .endIndex = currentIndex + tokenSize,
            .startColumn = currentColumn,
            .endColumn = currentColumn + tokenSize,
            .startLine = currentLine,
            .endLine = currentLine
        });
    AdvanceCurrentIndex(currentIndex, currentColumn);
    return tokenBuffer.AddToken({ .kind = tokenKind, .locationIndex = locationIndex });
};

[[nodiscard]] auto AddLexemeAndAdvance(TokenBuffer& tokenBuffer, const SourceTextSharedPtr& source, int& currentLine, int& currentIndex, int& currentColumn, TokenKind tokenKind, int startIndex, int startColumn, int startLine) noexcept
{
    auto length = currentIndex - startIndex;
    auto identifierIndex = tokenBuffer.AddLexeme(QStringView(source->text).sliced(startIndex, length));
    auto locationIndex = tokenBuffer.AddSourceLocation(
        {
            .source = source,
            .startIndex = startIndex,
            .endIndex = currentIndex,
            .startColumn = startColumn,
            .endColumn = currentColumn,
            .startLine = startLine,
            .endLine = currentLine
        });
    return tokenBuffer.AddToken({ .kind = tokenKind, .kindIndex = identifierIndex, .locationIndex = locationIndex });
};

auto LexIdentifier(TokenBuffer& tokenBuffer, const SourceTextSharedPtr& source, int& currentLine, int& currentIndex, int& currentColumn) noexcept
{
    auto startIndex = currentIndex;
    auto startLine = currentLine;
    auto startColumn = currentColumn;
    while (IsLetterOrNumberOrUnderscore(PeekCurrentChar(source, currentIndex)))
        AdvanceCurrentIndex(currentIndex, currentColumn);

    return AddLexemeAndAdvance(tokenBuffer, source, currentLine, currentIndex, currentColumn, TokenKind::Identifier, startIndex, startColumn, startLine);
};

auto LexNumber(TokenBuffer& tokenBuffer, const SourceTextSharedPtr& source, int& currentLine, int& currentIndex, int& currentColumn) noexcept
{
    auto startIndex = currentIndex;
    auto startLine = currentLine;
    auto startColumn = currentColumn;

    auto current = PeekCurrentChar(source, currentIndex);
    while (current.isNumber() || (current == QChar('_') && PeekNextChar(source, currentIndex) != QChar('.')))
    {
        AdvanceCurrentIndex(currentIndex, currentColumn);
        current = PeekCurrentChar(source, currentIndex);
    }

    if (current == QChar('.') && PeekNextChar(source, currentIndex).isNumber())
    {
        AdvanceCurrentIndex(currentIndex, currentColumn);

        while (IsNumberOrUnderscore(PeekCurrentChar(source, currentIndex)))
            AdvanceCurrentIndex(currentIndex, currentColumn);
    }

    return AddLexemeAndAdvance(tokenBuffer, source, currentLine, currentIndex, currentColumn, TokenKind::Number, startIndex, startColumn, startLine);
};

auto LexString(TokenBuffer& tokenBuffer, DiagnosticsBag& diagnostics, const SourceTextSharedPtr& source, int& currentLine, int& currentIndex, int& currentColumn) noexcept
{
    auto startIndex = currentIndex;
    auto startLine = currentLine;
    auto startColumn = currentColumn;

    // Consume opening quotation mark
    AdvanceCurrentIndex(currentIndex, currentColumn);
    while (PeekCurrentChar(source, currentIndex) != QChar('\"') && PeekCurrentChar(source, currentIndex) != QChar('\0'))
        AdvanceCurrentIndex(currentIndex, currentColumn);

    if (PeekCurrentChar(source, currentIndex) == QChar('\"'))
    {
        // Consume closing quotation mark
        AdvanceCurrentIndex(currentIndex, currentColumn);
        return AddLexemeAndAdvance(tokenBuffer, source, currentLine, currentIndex, currentColumn, TokenKind::String, startIndex, startColumn, startLine);
    }
    else
    {
        auto token = AddLexemeAndAdvance(tokenBuffer, source, currentLine, currentIndex, currentColumn, TokenKind::Error, startIndex, startColumn, startLine);
        auto& location = tokenBuffer.GetSourceLocation(token.locationIndex);
        diagnostics.AddError(DiagnosticKind::_0002_UnterminatedString, location);
        return token;
    }
};

[[nodiscard]] TokenBuffer Lex(const SourceTextSharedPtr& source, DiagnosticsBag& diagnostics) noexcept
{
    TokenBuffer tokenBuffer{ static_cast<int>(source->text.size()) };
    int currentIndex = 0;
    int currentLine = 1;
    int currentColumn = 1;

    while (true)
    {
        auto current = PeekCurrentChar(source, currentIndex);

        switch (current.unicode())
        {
            case '\r':
            {
                if (PeekNextChar(source, currentIndex) == QChar('\n'))
                    AdvanceCurrentIndex(currentIndex, currentColumn);

                AdvanceCurrentIndexAndResetLine(currentIndex, currentLine, currentColumn);
                break;
            }
            case '\n':
            {
                AdvanceCurrentIndexAndResetLine(currentIndex, currentLine, currentColumn);
                break;
            }
            case '\t':
            case ' ':
            {
                AdvanceCurrentIndex(currentIndex, currentColumn);
                break;
            }
            case '\0':
            {
                AddTokenKindAndAdvance(tokenBuffer, source, currentLine, currentIndex, currentColumn, TokenKind::EndOfFile);
                return tokenBuffer;
            }

            case '+':
            {
                AddTokenKindAndAdvance(tokenBuffer, source, currentLine, currentIndex, currentColumn, TokenKind::Plus);
                break;
            }
            case '-':
            {
                AddTokenKindAndAdvance(tokenBuffer, source, currentLine, currentIndex, currentColumn, TokenKind::Minus);
                break;
            }
            case '*':
            {
                AddTokenKindAndAdvance(tokenBuffer, source, currentLine, currentIndex, currentColumn, TokenKind::Star);
                break;
            }
            case '/':
            {
                AddTokenKindAndAdvance(tokenBuffer, source, currentLine, currentIndex, currentColumn, TokenKind::Slash);
                break;
            }
            case '.':
            {
                AddTokenKindAndAdvance(tokenBuffer, source, currentLine, currentIndex, currentColumn, TokenKind::Dot);
                break;
            }
            case ',':
            {
                AddTokenKindAndAdvance(tokenBuffer, source, currentLine, currentIndex, currentColumn, TokenKind::Comma);
                break;
            }
            case '=':
            {
                AddTokenKindAndAdvance(tokenBuffer, source, currentLine, currentIndex, currentColumn, TokenKind::Equal);
                break;
            }
            case '(':
            {
                AddTokenKindAndAdvance(tokenBuffer, source, currentLine, currentIndex, currentColumn, TokenKind::OpenParenthesis);
                break;
            }
            case ')':
            {
                AddTokenKindAndAdvance(tokenBuffer, source, currentLine, currentIndex, currentColumn, TokenKind::CloseParenthesis);
                break;
            }
            case '{':
            {
                AddTokenKindAndAdvance(tokenBuffer, source, currentLine, currentIndex, currentColumn, TokenKind::OpenBracket);
                break;
            }
            case '}':
            {
                AddTokenKindAndAdvance(tokenBuffer, source, currentLine, currentIndex, currentColumn, TokenKind::CloseBracket);
                break;
            }
            case '\"':
            {
                LexString(tokenBuffer, diagnostics, source, currentLine, currentIndex, currentColumn);
                break;
            }
            default:
            {
                if (IsLetterOrUnderscore(current))
                {
                    LexIdentifier(tokenBuffer, source, currentLine, currentIndex, currentColumn);
                    break;
                }
                else if (current.isNumber())
                {
                    LexNumber(tokenBuffer, source, currentLine, currentIndex, currentColumn);
                    break;
                }

                auto token = AddTokenKindAndAdvance(tokenBuffer, source, currentLine, currentIndex, currentColumn, TokenKind::Unknown);
                const auto& location = tokenBuffer.GetSourceLocation(token.locationIndex);
                diagnostics.AddError(DiagnosticKind::_0001_FoundIllegalCharacter, location);
                break;
            }
        }
    }
}
