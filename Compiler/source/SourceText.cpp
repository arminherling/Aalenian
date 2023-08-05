#include "SourceText.h"

SourceText::SourceText(
    const QString& text,
    const QString& filePath)
    : m_text(text)
    , m_filePath(filePath)
{
}

QStringView SourceText::text()
{
    return m_text;
}

QStringView SourceText::filePath()
{
    return m_filePath;
}
