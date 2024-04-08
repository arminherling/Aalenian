#pragma once

#include <Defines.h>
#include <Syntax/TokenKind.h>

#include <QString>

struct COMPILER_API Token
{
    TokenKind kind = TokenKind::Unknown;
    i32 lexemeIndex = -1;
    i32 locationIndex = -1;

    [[nodiscard]] static Token ToError(const Token& token) const noexcept
    {
        return { .kind = TokenKind::Error, .locationIndex = token.locationIndex };
    }
};
