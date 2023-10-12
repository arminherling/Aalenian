#pragma once

#include "CompilerApi.h"

#include "DiagnosticsBag.h"
#include "LexerResult.h"
#include "SourceText.h"
#include "Token.h"

class COMPILER_API Lexer
{
public:
    Lexer(const SourceTextSharedPtr& source);

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

    Token CreateLexemeAndToken(TokenKind kind, int startIndex, int startLine, int startColumn);
    Token CreateTokenAndAdvance(TokenKind kind, const QString& lexeme);

    SourceTextSharedPtr source;
    DiagnosticsBag diagnostics;
    int currentIndex;
    int currentLine;
    int currentColumn;
};
