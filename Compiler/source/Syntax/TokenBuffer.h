#pragma once

#include <API.h>
#include <TypeDefs.h>
#include <Compiler/DiagnosticsBag.h>
#include <Syntax/Token.h>
#include <Text/SourceText.h>
#include <Text/SourceLocation.h>

#include <vector>

class COMPILER_API TokenBuffer
{
public:
    TokenBuffer(i32 initialSize);

    Token AddToken(const Token& token) noexcept;
    i32 AddLexeme(const QStringView& lexeme) noexcept;
    i32 AddSourceLocation(const SourceLocation& sourceLocation) noexcept;

    i32 size() const noexcept;
    const Token& operator[](i32 position) const noexcept;

    const SourceLocation& GetSourceLocation(i32 sourceLocationIndex) const noexcept;
    const QStringView& GetLexeme(i32 lexemeIndex) const noexcept;

private:
    std::vector<Token> tokens;
    std::vector<QStringView> lexemes;
    std::vector<SourceLocation> sourceLocations;
};
