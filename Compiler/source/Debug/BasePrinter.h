#pragma once

#include <Defines.h>
#include <QTextStream>
#include <QString>

class COMPILER_API BasePrinter
{
public:
    BasePrinter(i32 indentation = 4);

protected:
    void PushIndentation() { m_indentationLevel++; }
    void PopIndentation() { m_indentationLevel--; }
    QTextStream& stream() { return m_stream; }
    QByteArray toUtf8() { return m_output.toUtf8(); }

    QString Indentation() { return QString(" ").repeated(m_indentation * m_indentationLevel); }
    QString NewLine() { return QString("\r\n"); }

    i32 m_indentation;
    i32 m_indentationLevel;
    QString m_output;
    QTextStream m_stream;
};

