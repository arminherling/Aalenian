#pragma once

#include <AalTest/API.h>
#include <chrono>
#include <QString>
#include <tuple>

AALTEST_API QString Stringify(bool value);
AALTEST_API QString Stringify(int value);
AALTEST_API QString Stringify(const char* str);
AALTEST_API QString Stringify(const QString& string);
AALTEST_API QString Stringify(const QStringView string);
AALTEST_API QString Stringify(const std::chrono::nanoseconds& ns);

template<class T>
QString Stringify(T t)
{
    return QString("?");
}

template<class ...Ts>
QString Stringify(const std::tuple<Ts...>& tuple)
{
    auto converter = [](const auto& ...args) { return QStringList{ Stringify(args)... }; };
    auto parts = std::apply(converter, tuple);
    return QString("(%1)").arg(parts.join(", "));
}
