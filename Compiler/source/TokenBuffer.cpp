#include "TokenBuffer.h"

#include <unordered_map>

namespace V2
{
    void DiagnosticsBag::AddWarning(DiagnosticKind kind, const V2::SourceLocation& location)
    {
        diagnostics.emplace_back(DiagnosticLevel::Warning, kind, location);
    }

    void DiagnosticsBag::AddError(DiagnosticKind kind, const V2::SourceLocation& location)
    {
        diagnostics.emplace_back(DiagnosticLevel::Error, kind, location);
    }

    const std::vector<V2::Diagnostic>& DiagnosticsBag::Diagnostics()
    {
        return diagnostics;
    }

    std::unordered_map<TokenKind, int> InitializeTokenSizes()
    {
        return {
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

    int TokenSize(TokenKind kind)
    {
        static const auto tokenSizes = InitializeTokenSizes();
        if (auto result = tokenSizes.find(kind); result != tokenSizes.end())
            return result->second;

        return 0;
    }

    TokenBuffer::TokenBuffer(int initialSize)
        : tokens{}
        , sourceLocations{}
    {
        tokens.reserve(initialSize);
        lexemes.reserve(initialSize);
        sourceLocations.reserve(initialSize);
    }

    Token TokenBuffer::AddToken(const Token& token) noexcept
    {
        tokens.push_back(token);
        return token;
    }

    int TokenBuffer::AddLexeme(const QStringView& lexeme) noexcept
    {
        lexemes.push_back(lexeme);
        return lexemes.size() - 1;
    }

    int TokenBuffer::AddSourceLocation(const V2::SourceLocation& sourceLocation) noexcept
    {
        sourceLocations.push_back(sourceLocation);
        return sourceLocations.size() - 1;
    }

    int TokenBuffer::size() const noexcept
    {
        return tokens.size();
    }

    const Token& TokenBuffer::operator[](int position) const noexcept
    {
        return tokens.at(position);
    }

    const SourceLocation& TokenBuffer::GetSourceLocation(int sourceLocationIndex) const noexcept
    {
        return sourceLocations.at(sourceLocationIndex);
    }

    const QStringView& TokenBuffer::GetLexeme(int lexemeIndex) const noexcept
    {
        return lexemes.at(lexemeIndex);
    }

    TokenBuffer OldLex(const SourceTextSharedPtr& source, DiagnosticsBag& diagnostics) noexcept
    {
        TokenBuffer tokenBuffer{ static_cast<int>(source->text.size()) };
        int currentIndex = 0;
        int currentLine = 1;
        int currentColumn = 1;

        auto PeekChar = [&](int offset) -> QChar {
            auto charIndex = currentIndex + offset;
            if (charIndex >= source->text.length())
                return '\0';

            return source->text[charIndex];
        };

        auto PeekCurrentChar = [&]() { return PeekChar(0); };
        auto PeekNextChar = [&]() { return PeekChar(1); };

        auto AdvanceCurrentIndex = [&]() {
            currentIndex++;
            currentColumn++;
        };

        auto AdvanceCurrentIndexAndResetLine = [&]()
        {
            AdvanceCurrentIndex();
            currentLine++;
            currentColumn = 1;
        };

        auto AddTokenKindAndAdvance = [&](TokenKind tokenKind)
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
            AdvanceCurrentIndex();
            return tokenBuffer.AddToken({ .kind = tokenKind, .locationIndex = locationIndex });
        };

        auto AddLexemeAndAdvance = [&](TokenKind tokenKind, int startIndex, int startColumn, int startLine)
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

        auto LexIdentifier = [&]()
        {
            auto startIndex = currentIndex;
            auto startLine = currentLine;
            auto startColumn = currentColumn;
            while (PeekCurrentChar() == '_' || PeekCurrentChar().isLetterOrNumber())
                AdvanceCurrentIndex();

            return AddLexemeAndAdvance(TokenKind::Identifier, startIndex, startColumn, startLine);
        };

        auto LexNumber = [&]()
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

            return AddLexemeAndAdvance(TokenKind::Number, startIndex, startColumn, startLine);
        };

        auto LexString = [&]()
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
                return AddLexemeAndAdvance(TokenKind::String, startIndex, startColumn, startLine);
            }
            else
            {
                auto token = AddLexemeAndAdvance(TokenKind::Error, startIndex, startColumn, startLine);
                auto& location = tokenBuffer.GetSourceLocation(token.locationIndex);
                diagnostics.AddError(DiagnosticKind::_0002_UnterminatedString, location);
                return token;
            }
        };

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
                case '\0':
                {
                    AddTokenKindAndAdvance(TokenKind::EndOfFile);
                    return tokenBuffer;
                }

                case '+':
                {
                    AddTokenKindAndAdvance(TokenKind::Plus);
                    break;
                }
                case '-':
                {
                    AddTokenKindAndAdvance(TokenKind::Minus);
                    break;
                }
                case '*':
                {
                    AddTokenKindAndAdvance(TokenKind::Star);
                    break;
                }
                case '/':
                {
                    AddTokenKindAndAdvance(TokenKind::Slash);
                    break;
                }
                case '.':
                {
                    AddTokenKindAndAdvance(TokenKind::Dot);
                    break;
                }
                case ',':
                {
                    AddTokenKindAndAdvance(TokenKind::Comma);
                    break;
                }
                case '=':
                {
                    AddTokenKindAndAdvance(TokenKind::Equal);
                    break;
                }
                case '(':
                {
                    AddTokenKindAndAdvance(TokenKind::OpenParenthesis);
                    break;
                }
                case ')':
                {
                    AddTokenKindAndAdvance(TokenKind::CloseParenthesis);
                    break;
                }
                case '{':
                {
                    AddTokenKindAndAdvance(TokenKind::OpenBracket);
                    break;
                }
                case '}':
                {
                    AddTokenKindAndAdvance(TokenKind::CloseBracket);
                    break;
                }
                case '\"':
                {
                    LexString();
                    break;
                }
                default:
                {
                    if (current == '_' || current.isLetter())
                    {
                        LexIdentifier();
                        break;
                    }
                    else if (current.isNumber())
                    {
                        LexNumber();
                        break;
                    }

                    auto token = AddTokenKindAndAdvance(TokenKind::Unknown);
                    auto& location = tokenBuffer.GetSourceLocation(token.locationIndex);
                    diagnostics.AddError(DiagnosticKind::_0001_FoundIllegalCharacter, location);
                    break;
                }
            }
        }
    }

    // Version 2

    [[nodiscard]] auto PeekChar2(const SourceTextSharedPtr& source, int& currentIndex, int offset) noexcept {
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

    [[nodiscard]] auto PeekCurrentChar2(const SourceTextSharedPtr& source, int& currentIndex) noexcept { return PeekChar2(source, currentIndex, 0); };
    [[nodiscard]] auto PeekNextChar2(const SourceTextSharedPtr& source, int& currentIndex) noexcept { return PeekChar2(source, currentIndex, 1); };

    auto AdvanceCurrentIndex2(int& currentIndex, int& currentColumn) noexcept
    {
        currentIndex++;
        currentColumn++;
    };

    auto AdvanceCurrentIndexAndResetLine2(int& currentIndex, int& currentLine, int& currentColumn) noexcept
    {
        currentIndex++;
        currentLine++;
        currentColumn = 1;
    };

    auto AddTokenKindAndAdvance2(TokenBuffer& tokenBuffer, const SourceTextSharedPtr& source, int& currentLine, int& currentIndex, int& currentColumn, TokenKind tokenKind) noexcept
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
        AdvanceCurrentIndex2(currentIndex, currentColumn);
        return tokenBuffer.AddToken({ .kind = tokenKind, .locationIndex = locationIndex });
    };

    [[nodiscard]] auto AddLexemeAndAdvance2(TokenBuffer& tokenBuffer, const SourceTextSharedPtr& source, int& currentLine, int& currentIndex, int& currentColumn, TokenKind tokenKind, int startIndex, int startColumn, int startLine) noexcept
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

    auto LexIdentifier2(TokenBuffer& tokenBuffer, const SourceTextSharedPtr& source, int& currentLine, int& currentIndex, int& currentColumn) noexcept
    {
        auto startIndex = currentIndex;
        auto startLine = currentLine;
        auto startColumn = currentColumn;
        while (IsLetterOrNumberOrUnderscore(PeekCurrentChar2(source, currentIndex)))
            AdvanceCurrentIndex2(currentIndex, currentColumn);

        return AddLexemeAndAdvance2(tokenBuffer, source, currentLine, currentIndex, currentColumn, TokenKind::Identifier, startIndex, startColumn, startLine);
    };

    auto LexNumber2(TokenBuffer& tokenBuffer, const SourceTextSharedPtr& source, int& currentLine, int& currentIndex, int& currentColumn) noexcept
    {
        auto startIndex = currentIndex;
        auto startLine = currentLine;
        auto startColumn = currentColumn;

        auto current = PeekCurrentChar2(source, currentIndex);
        while (current.isNumber() || (current == QChar('_') && PeekNextChar2(source, currentIndex) != QChar('.')))
        {
            AdvanceCurrentIndex2(currentIndex, currentColumn);
            current = PeekCurrentChar2(source, currentIndex);
        }

        if (current == QChar('.') && PeekNextChar2(source, currentIndex).isNumber())
        {
            AdvanceCurrentIndex2(currentIndex, currentColumn);

            while (IsNumberOrUnderscore(PeekCurrentChar2(source, currentIndex)))
                AdvanceCurrentIndex2(currentIndex, currentColumn);
        }

        return AddLexemeAndAdvance2(tokenBuffer, source, currentLine, currentIndex, currentColumn, TokenKind::Number, startIndex, startColumn, startLine);
    };

    auto LexString2(TokenBuffer& tokenBuffer, DiagnosticsBag& diagnostics, const SourceTextSharedPtr& source, int& currentLine, int& currentIndex, int& currentColumn) noexcept
    {
        auto startIndex = currentIndex;
        auto startLine = currentLine;
        auto startColumn = currentColumn;

        // Consume opening quotation mark
        AdvanceCurrentIndex2(currentIndex, currentColumn);
        while (PeekCurrentChar2(source, currentIndex) != QChar('\"') && PeekCurrentChar2(source, currentIndex) != QChar('\0'))
            AdvanceCurrentIndex2(currentIndex, currentColumn);

        if (PeekCurrentChar2(source, currentIndex) == QChar('\"'))
        {
            // Consume closing quotation mark
            AdvanceCurrentIndex2(currentIndex, currentColumn);
            return AddLexemeAndAdvance2(tokenBuffer, source, currentLine, currentIndex, currentColumn, TokenKind::String, startIndex, startColumn, startLine);
        }
        else
        {
            auto token = AddLexemeAndAdvance2(tokenBuffer, source, currentLine, currentIndex, currentColumn, TokenKind::Error, startIndex, startColumn, startLine);
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
            auto current = PeekCurrentChar2(source, currentIndex);

            switch (current.unicode())
            {
                case '\r':
                {
                    if (PeekNextChar2(source, currentIndex) == QChar('\n'))
                        AdvanceCurrentIndex2(currentIndex, currentColumn);

                    AdvanceCurrentIndexAndResetLine2(currentIndex, currentLine, currentColumn);
                    break;
                }
                case '\n':
                {
                    AdvanceCurrentIndexAndResetLine2(currentIndex, currentLine,  currentColumn);
                    break;
                }
                case '\t':
                case ' ':
                {
                    AdvanceCurrentIndex2(currentIndex, currentColumn);
                    break;
                }
                case '\0':
                {
                    AddTokenKindAndAdvance2(tokenBuffer, source, currentLine, currentIndex, currentColumn, TokenKind::EndOfFile);
                    return tokenBuffer;
                }

                case '+':
                {
                    AddTokenKindAndAdvance2(tokenBuffer, source, currentLine, currentIndex, currentColumn, TokenKind::Plus);
                    break;
                }
                case '-':
                {
                    AddTokenKindAndAdvance2(tokenBuffer, source, currentLine, currentIndex, currentColumn, TokenKind::Minus);
                    break;
                }
                case '*':
                {
                    AddTokenKindAndAdvance2(tokenBuffer, source, currentLine, currentIndex, currentColumn, TokenKind::Star);
                    break;
                }
                case '/':
                {
                    AddTokenKindAndAdvance2(tokenBuffer, source, currentLine, currentIndex, currentColumn, TokenKind::Slash);
                    break;
                }
                case '.':
                {
                    AddTokenKindAndAdvance2(tokenBuffer, source, currentLine, currentIndex, currentColumn, TokenKind::Dot);
                    break;
                }
                case ',':
                {
                    AddTokenKindAndAdvance2(tokenBuffer, source, currentLine, currentIndex, currentColumn, TokenKind::Comma);
                    break;
                }
                case '=':
                {
                    AddTokenKindAndAdvance2(tokenBuffer, source, currentLine, currentIndex, currentColumn, TokenKind::Equal);
                    break;
                }
                case '(':
                {
                    AddTokenKindAndAdvance2(tokenBuffer, source, currentLine, currentIndex, currentColumn, TokenKind::OpenParenthesis);
                    break;
                }
                case ')':
                {
                    AddTokenKindAndAdvance2(tokenBuffer, source, currentLine, currentIndex, currentColumn, TokenKind::CloseParenthesis);
                    break;
                }
                case '{':
                {
                    AddTokenKindAndAdvance2(tokenBuffer, source, currentLine, currentIndex, currentColumn, TokenKind::OpenBracket);
                    break;
                }
                case '}':
                {
                    AddTokenKindAndAdvance2(tokenBuffer, source, currentLine, currentIndex, currentColumn, TokenKind::CloseBracket);
                    break;
                }
                case '\"':
                {
                    LexString2(tokenBuffer, diagnostics, source, currentLine, currentIndex, currentColumn);
                    break;
                }
                default:
                {
                    if (IsLetterOrUnderscore(current))
                    {
                        LexIdentifier2(tokenBuffer, source, currentLine, currentIndex, currentColumn);
                        break;
                    }
                    else if (current.isNumber())
                    {
                        LexNumber2(tokenBuffer, source, currentLine, currentIndex, currentColumn);
                        break;
                    }

                    auto token = AddTokenKindAndAdvance2(tokenBuffer, source, currentLine, currentIndex, currentColumn, TokenKind::Unknown);
                    const auto& location = tokenBuffer.GetSourceLocation(token.locationIndex);
                    diagnostics.AddError(DiagnosticKind::_0001_FoundIllegalCharacter, location);
                    break;
                }
            }
        }
    }
}
