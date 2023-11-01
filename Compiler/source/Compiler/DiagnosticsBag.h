#pragma once

#include <API.h>
#include <Compiler/Diagnostic.h>

#include <vector>

class COMPILER_API DiagnosticsBag
{
public:
    DiagnosticsBag() = default;

    void AddWarning(DiagnosticKind kind, const SourceLocation& location);
    void AddError(DiagnosticKind kind, const SourceLocation& location);

    const std::vector<Diagnostic>& Diagnostics();

private:
    std::vector<Diagnostic> diagnostics;
};
