#pragma once

#include "CompilerApi.h"

#include <QStringView>

struct COMPILER_API SourceLocation
{
    SourceLocation(const QStringView& sourcetext, int firstIndex, int lastIndex);

    QStringView sourceText;
    int firstIndex;
    int lastIndex;
};
