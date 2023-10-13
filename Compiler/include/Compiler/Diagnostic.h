#pragma once

#include "CompilerApi.h"

#include "DiagnosticLevel.h"
#include "DiagnosticKind.h"
#include "SourceLocation.h"

struct COMPILER_API Diagnostic
{
    DiagnosticLevel level = DiagnosticLevel::Unknown;
    DiagnosticKind kind = DiagnosticKind::Unknown;
    SourceLocation location;
};
