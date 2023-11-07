#pragma once

#include <API.h>

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
int COMPILER_API UnaryOperatorPrecedence(TokenKind kind);
int COMPILER_API BinaryOperatorPrecedence(TokenKind kind);
