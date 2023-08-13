#pragma once

#include "CompilerApi.h"

#include <QString>
#include <QStringView>

struct COMPILER_API SourceLocation
{
    SourceLocation(const QStringView& sourcetext, int firstIndex, int lastIndex);

    QString Stringify() const;

    QStringView sourceText;
    int firstIndex;
    int lastIndex;
};
