#pragma once

#include "CompilerApi.h"

#include <QStringView>

struct COMPILER_API SourceLineAndColumns
{
    int startLine;
    int startColumn;
    int endLine;
    int endColumn;
};

COMPILER_API SourceLineAndColumns StartAndEndPositions(const QStringView& sourceText, int firstIndex, int lastIndex);
