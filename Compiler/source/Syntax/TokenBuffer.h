#pragma once

#include <API.h>
#include <Compiler/DiagnosticsBag.h>
#include <Syntax/Token.h>
#include <Text/SourceText.h>
#include <Text/SourceLocation.h>

#include <vector>

class COMPILER_API TokenBuffer
{
public:
    TokenBuffer(int initialSize);

    Token AddToken(const Token& token) noexcept;
    int AddLexeme(const QStringView& lexeme) noexcept;
    int AddSourceLocation(const SourceLocation& sourceLocation) noexcept;

    int size() const noexcept;
    const Token& operator[](int position) const noexcept;

    const SourceLocation& GetSourceLocation(int sourceLocationIndex) const noexcept;
    const QStringView& GetLexeme(int lexemeIndex) const noexcept;

private:
    std::vector<Token> tokens;
    std::vector<QStringView> lexemes;
    std::vector<SourceLocation> sourceLocations;
};
