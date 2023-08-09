#include "LexerResult.h"

LexerResult::LexerResult(
    const DiagnosticsBag& diagnostics,
    const QList<Token>& tokens)
    : diagnostics(diagnostics)
    , tokens(tokens)
{
}
