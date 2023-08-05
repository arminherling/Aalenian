#pragma once

#include "CompilerApi.h"

#include "SourceText.h"
#include "Token.h"

class COMPILER_API Lexer
{
public:
    Lexer(const SourceText& source);

    Token NextToken();
    
private:
    QChar PeekCurrentChar();
    QChar PeekNextChar();
    QChar PeekChar(int offset);
    void AdvanceCurrentIndex();
    void AdvanceCurrentIndexAndResetLine();

    Token LexIdentifier();
    Token LexNumber();
    Token LexString();

    Token CreateTokenAndAdvance(TokenKind kind, const QString& lexeme);

    SourceText m_source;
    int m_index;
    int m_lineNumber;
};
