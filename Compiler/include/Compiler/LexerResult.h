#pragma once

#include "CompilerApi.h"

#include "Token.h"
#include "DiagnosticsBag.h"

#include <QList>

struct COMPILER_API LexerResult
{
    LexerResult(const DiagnosticsBag& diagnostics, const QList<Token>& tokens);

    DiagnosticsBag diagnostics;
    QList<Token> tokens;
};
