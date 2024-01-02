#pragma once

#include <QString>
#include <tuple>
#include <AalTest/API.h>

AALTEST_API QString Stringify(bool value);
AALTEST_API QString Stringify(int value);
AALTEST_API QString Stringify(const char* str);
AALTEST_API QString Stringify(const QString& string);

template<class T>
QString Stringify(T t)
{
    return QString("missing stringify case");
}

template<class ...Ts>
QString Stringify(const std::tuple<Ts...>& tuple)
{
    auto converter = [](const auto& ...args) { return QStringList{ Stringify(args)... }; };
    auto parts = std::apply(converter, tuple);
    return QString("(%1)").arg(parts.join(", "));
}
