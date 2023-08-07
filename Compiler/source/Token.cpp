#include "Token.h"

Token::Token(
    TokenKind kind, 
    const QString& lexeme, 
    const SourceLocation& location)
    : kind(kind)
    , lexeme(lexeme)
    , location(location)
{
}
