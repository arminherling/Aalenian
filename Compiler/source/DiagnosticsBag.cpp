#include "DiagnosticsBag.h"

void DiagnosticsBag::AddWarning(DiagnosticKind kind, const SourceLocation& location)
{
    diagnostics.emplace_back(DiagnosticLevel::Warning, kind, location);
}

void DiagnosticsBag::AddError(DiagnosticKind kind, const SourceLocation& location)
{
    diagnostics.emplace_back(DiagnosticLevel::Error, kind, location);
}

const std::vector<Diagnostic>& DiagnosticsBag::Diagnostics()
{
    return diagnostics;
}
