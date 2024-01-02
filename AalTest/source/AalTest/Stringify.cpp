#include "Stringify.h"

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
    return QString("\"%1\"").arg(QString::fromLocal8Bit(str));
}

QString Stringify(const QString& string)
{
    return QString("\"%1\"").arg(string);
}
