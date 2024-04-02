#pragma once

#include <Defines.h>
#include <QString>

enum class COMPILER_API TokenKind
{
    Unknown,
    Error,

    Plus,
    Minus,
    Star,
    Slash,
    Dot,
    Colon,
    DoubleColon,
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

COMPILER_API QString Stringify(TokenKind kind);
COMPILER_API i32 UnaryOperatorPrecedence(TokenKind kind);
COMPILER_API i32 BinaryOperatorPrecedence(TokenKind kind);
