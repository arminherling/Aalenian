#pragma once

#include "CompilerApi.h"
#include "TokenKind.h"
#include "SourceLocation.h"

#include <QString>

struct COMPILER_API Token
{
    Token(TokenKind kind, const QString& lexeme, const SourceLocation& location);

    TokenKind kind;
    QString lexeme;
    SourceLocation location;
};
