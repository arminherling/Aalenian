#include <Syntax/TokenBuffer.h>

TokenBuffer::TokenBuffer(i32 initialSize)
    : tokens{}
    , lexemes{}
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

i32 TokenBuffer::AddLexeme(const QStringView& lexeme) noexcept
{
    lexemes.push_back(lexeme);
    return lexemes.size() - 1;
}

i32 TokenBuffer::AddSourceLocation(const SourceLocation& sourceLocation) noexcept
{
    sourceLocations.push_back(sourceLocation);
    return sourceLocations.size() - 1;
}

i32 TokenBuffer::size() const noexcept
{
    return tokens.size();
}

const Token& TokenBuffer::operator[](i32 position) const noexcept
{
    return tokens.at(position);
}

const SourceLocation& TokenBuffer::GetSourceLocation(const Token& token) const noexcept
{
    return sourceLocations.at(token.locationIndex);
}

const QStringView& TokenBuffer::GetLexeme(i32 lexemeIndex) const noexcept
{
    return lexemes.at(lexemeIndex);
}
