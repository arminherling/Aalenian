#pragma once

#include "CompilerApi.h"
#include "TokenKind.h"

#include <QString>

struct COMPILER_API Token
{
    TokenKind kind = TokenKind::Unknown;
    int kindIndex = -1;
    int locationIndex = -1;

    [[nodiscard]] static Token ToError(const Token& token) noexcept
    {
        return { .kind = TokenKind::Error, .locationIndex = token.locationIndex };
    }
};
