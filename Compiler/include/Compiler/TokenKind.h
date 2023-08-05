#pragma once

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
