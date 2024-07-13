#pragma once

#include <Compiler/API.h>

#include <QByteArray>
#include <QString>

class COMPILER_API File
{
public:
    static QByteArray ReadAll(const QString& filePath);
    static QString ReadAllText(const QString& filePath);
};

