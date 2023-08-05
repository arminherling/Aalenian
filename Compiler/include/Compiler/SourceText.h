#pragma once

#include "CompilerApi.h"

#include <QString>

class COMPILER_API SourceText
{
public:
    SourceText(const QString& text, const QString& filePath = QString());

    QStringView text();
    QStringView filePath();

private:
    QString m_text;
    QString m_filePath;
};
