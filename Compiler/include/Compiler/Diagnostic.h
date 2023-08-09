#pragma once

#include "CompilerApi.h"

#include "DiagnosticLevel.h"
#include "DiagnosticKind.h"
#include "SourceLocation.h"

struct COMPILER_API Diagnostic
{
    Diagnostic(DiagnosticLevel level, DiagnosticKind kind, SourceLocation location);

    DiagnosticLevel level;
    DiagnosticKind kind;
    SourceLocation location;
};
