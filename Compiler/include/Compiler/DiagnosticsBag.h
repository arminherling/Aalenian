#pragma once

#include "CompilerApi.h"

#include "Diagnostic.h"

#include <QList>

class COMPILER_API DiagnosticsBag
{
public:
    DiagnosticsBag() = default;

    void AddWarning(DiagnosticKind kind, SourceLocation location);
    void AddError(DiagnosticKind kind, SourceLocation location);

    QList<Diagnostic> Diagnostics();

private:
    QList<Diagnostic> diagnostics;
};
