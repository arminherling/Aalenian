#pragma once

#include "CompilerApi.h"

#include <QString>

struct COMPILER_API SourceText
{
    SourceText(const QString& text, const QString& filePath = QString());

    QString text;
    QString filePath;
};