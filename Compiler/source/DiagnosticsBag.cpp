#include "DiagnosticsBag.h"

void DiagnosticsBag::AddWarning(DiagnosticKind kind, SourceLocation location)
{
    diagnostics.append(Diagnostic(DiagnosticLevel::Warning, kind, location));
}

void DiagnosticsBag::AddError(DiagnosticKind kind, SourceLocation location)
{
    diagnostics.append(Diagnostic(DiagnosticLevel::Error, kind, location));
}

QList<Diagnostic> DiagnosticsBag::Diagnostics()
{
    return diagnostics;
}
