#pragma once

#include "CompilerApi.h"
#include "SourceText.h"

struct COMPILER_API SourceLocation
{
    SourceTextSharedPtr source;
    int startIndex = -1;
    int endIndex = -1;
    int startColumn = -1;
    int endColumn = -1;
    int startLine = -1;
    int endLine = -1;
};
