#pragma once

#include "CompilerApi.h"
#include "TokenKind.h"

#include <QString>

struct COMPILER_API Token
{
    TokenKind kind = TokenKind::Unknown;
    int kindIndex = -1;
    int locationIndex = -1;
};
