#pragma once

#include "CompilerApi.h"

#include <QString>

enum class TokenKind
{
    Plus,
    Minus,
    Star,
    Slash,
    Dot,
    Comma,
    Equal,
    OpenParenthesis,
    CloseParenthesis,
    OpenBracket,
    CloseBracket,

    Identifier,
    Number,
    String,

    Error,
    Unknown,
    EndOfFile
};

QString COMPILER_API Stringify(TokenKind kind);
