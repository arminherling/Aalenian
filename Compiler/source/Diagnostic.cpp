#include "Diagnostic.h"

Diagnostic::Diagnostic(
    DiagnosticLevel level, 
    DiagnosticKind kind, 
    SourceLocation location)
    : level(level)
    , kind(kind)
    , location(location)
{
}
