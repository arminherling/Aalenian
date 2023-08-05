#pragma once

#include "CompilerApi.h"
#include "TokenKind.h"

#include <QString>

struct COMPILER_API Token
{
    Token(TokenKind kind, const QString& lexeme);

    TokenKind kind;
    QString lexeme;
};
