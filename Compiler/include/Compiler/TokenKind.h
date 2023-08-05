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

    Unknown,
    EndOfFile
};
