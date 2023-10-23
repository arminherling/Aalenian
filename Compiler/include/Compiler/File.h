#pragma once

#include "CompilerApi.h"

class COMPILER_API File
{
public:
    static QByteArray ReadAll(const QString& filePath);
    static QString ReadAllText(const QString& filePath);
};

