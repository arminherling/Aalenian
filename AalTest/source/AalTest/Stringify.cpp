#include "Stringify.h"
#include <QTextStream>

namespace 
{
    QString sanitize(QString input)
    {
        input.replace(QChar('\t'), QString("\\t"));
        input.replace(QChar('\r'), QString("\\r"));
        input.replace(QChar('\n'), QString("\\n"));
        return input;
    }
}

QString Stringify(bool value)
{
    return value ? QString("true") : QString("false");
}

QString Stringify(int value)
{
    return QString::number(value);
}

QString Stringify(const char* str)
{
    return QString("\"%1\"").arg(sanitize(QString::fromLocal8Bit(str)));
}

QString Stringify(const QStringView stringView)
{
    return Stringify(stringView.toString());
}

QString Stringify(const QString& string)
{
    return QString("\"%1\"").arg(sanitize(string));
}

QString Stringify(const std::chrono::nanoseconds& input)
{
    auto ns = input;

    using namespace std::chrono;

    auto s = duration_cast<seconds>(ns);
    ns -= s;
    auto ms = duration_cast<milliseconds>(ns);
    ns -= ms;
    auto us = duration_cast<microseconds>(ns);
    ns -= us;

    QString output;
    QTextStream stream{ &output };

    stream << s.count() << QString("s ");
    stream << QString::number(ms.count()).rightJustified(3, '0') << QString("ms ");
    stream << QString::number(us.count()).rightJustified(3, '0') << QString("μs ");
    stream << QString::number(ns.count()).rightJustified(3, '0') << QString("ns");

    return output;
}
