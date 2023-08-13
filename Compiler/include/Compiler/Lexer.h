#pragma once

#include "CompilerApi.h"

#include "DiagnosticsBag.h"
#include "LexerResult.h"
#include "SourceText.h"
#include "Token.h"

class COMPILER_API Lexer
{
public:
    Lexer(const SourceText& source);

    Token NextToken();
    LexerResult Lex();
    
private:
    QChar PeekCurrentChar();
    QChar PeekNextChar();
    QChar PeekChar(int offset);
    void AdvanceCurrentIndex();
    void AdvanceCurrentIndexAndResetLine();

    Token LexIdentifier();
    Token LexNumber();
    Token LexString();

    Token CreateLexemeAndToken(TokenKind kind, int startIndex);
    Token CreateTokenAndAdvance(TokenKind kind, const QChar& c);

    DiagnosticsBag diagnostics;
    SourceText source;
    int currentIndex;
    int lineNumber;
};
