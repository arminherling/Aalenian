#pragma once

#include <Defines.h>
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

    const SourceLocation& GetSourceLocation(const Token& token) const noexcept;
    const QStringView& GetLexeme(const Token& token) const noexcept;

private:
    std::vector<Token> tokens;
    std::vector<QStringView> lexemes;
    std::vector<SourceLocation> sourceLocations;
};
