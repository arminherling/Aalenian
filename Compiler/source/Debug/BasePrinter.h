#pragma once

#include <Defines.h>
#include <QTextStream>
#include <QString>

class COMPILER_API BasePrinter
{
public:
    BasePrinter(i32 indentation = 4);

protected:
    void PushIndentation() noexcept { m_indentationLevel++; }
    void PopIndentation() noexcept { m_indentationLevel--; }
    [[nodiscard]] QTextStream& stream() noexcept { return m_stream; }
    [[nodiscard]] QByteArray toUtf8() const noexcept { return m_output.toUtf8(); }

    [[nodiscard]] QString Indentation() const noexcept { return QString(" ").repeated(m_indentation * m_indentationLevel); }
    [[nodiscard]] QString NewLine() const noexcept { return QString("\r\n"); }

    i32 m_indentation;
    i32 m_indentationLevel;
    QString m_output;
    QTextStream m_stream;
};

