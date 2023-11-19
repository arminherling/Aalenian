#pragma once

#include <API.h>
#include <TypeDefs.h>

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

QString COMPILER_API Stringify(TokenKind kind);
i32 COMPILER_API UnaryOperatorPrecedence(TokenKind kind);
i32 COMPILER_API BinaryOperatorPrecedence(TokenKind kind);
