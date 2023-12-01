#pragma once

#include <Defines.h>
#include <Syntax/TokenKind.h>

#include <QString>

struct COMPILER_API Token
{
    TokenKind kind = TokenKind::Unknown;
    i32 kindIndex = -1;
    i32 locationIndex = -1;

    [[nodiscard]] static Token ToError(const Token& token) noexcept
    {
        return { .kind = TokenKind::Error, .locationIndex = token.locationIndex };
    }
};
