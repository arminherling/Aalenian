#include "Token.h"

Token::Token(TokenKind kind, const QString& lexeme)
    : kind(kind)
    , lexeme(lexeme)
{
}
