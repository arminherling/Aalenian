#pragma once

#include "CompilerApi.h"

#include <QString>

enum class TokenKind
{
    Unknown,
    Error,

    Plus,
    Minus,
    Star,
    Slash,
    Dot,
    Comma,
    Equal,
    Underscore,
    OpenParenthesis,
    CloseParenthesis,
    OpenBracket,
    CloseBracket,

    Identifier,
    Number,
    String,

    EndOfFile
};

QString COMPILER_API Stringify(TokenKind kind);
