#include "TokenBuffer.h"

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

int TokenBuffer::AddSourceLocation(const SourceLocation& sourceLocation) noexcept
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
