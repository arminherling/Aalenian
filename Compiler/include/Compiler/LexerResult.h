#pragma once

#include "CompilerApi.h"

#include "Token.h"

#include <QList>

struct COMPILER_API LexerResult
{
    LexerResult(const QList<Token>& tokens);

    QList<Token> tokens;
};
