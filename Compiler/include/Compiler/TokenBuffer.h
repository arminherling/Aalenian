#pragma once

#include "CompilerApi.h"

#include "SourceText.h"
#include "DiagnosticsBag.h"
#include "TokenKind.h"

#include <vector>

namespace V2
{
    struct COMPILER_API Token
    {
        TokenKind kind = TokenKind::Unknown;
        int kindIndex = -1;
        int locationIndex = -1;
    };

    struct COMPILER_API SourceLocation
    {
        SourceTextSharedPtr source;
        int startIndex = -1;
        int endIndex = -1;
        int startColumn = -1;
        int endColumn = -1;
        int startLine = -1;
        int endLine = -1;
    };

    struct COMPILER_API Diagnostic
    {
        DiagnosticLevel level;
        DiagnosticKind kind;
        V2::SourceLocation location;
    };

    class COMPILER_API DiagnosticsBag
    {
    public:
        DiagnosticsBag() = default;

        void AddWarning(DiagnosticKind kind, const V2::SourceLocation& location);
        void AddError(DiagnosticKind kind, const V2::SourceLocation& location);

        const std::vector<V2::Diagnostic>& Diagnostics();

    private:
        std::vector<V2::Diagnostic> diagnostics;
    };

    class COMPILER_API TokenBuffer
    {
    public:
        TokenBuffer(int initialSize);

        Token AddToken(const Token& token) noexcept;
        int AddLexeme(const QStringView& lexeme) noexcept;
        int AddSourceLocation(const V2::SourceLocation& sourceLocation) noexcept;

        int size() const noexcept;
        const Token& operator[](int position) const noexcept;

        const SourceLocation& GetSourceLocation(int sourceLocationIndex) const noexcept;
        const QStringView& GetLexeme(int lexemeIndex) const noexcept;

    private:
        std::vector<Token> tokens;
        std::vector<QStringView> lexemes;
        std::vector<SourceLocation> sourceLocations;
    };

    COMPILER_API TokenBuffer Lex(const SourceTextSharedPtr& source, DiagnosticsBag& diagnostics) noexcept;
    COMPILER_API TokenBuffer Lex2(const SourceTextSharedPtr& source, DiagnosticsBag& diagnostics) noexcept;
}
