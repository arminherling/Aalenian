#pragma once

#include <AalTest/API.h>
#include <exception>
#include <QString>
#include <source_location>

class AALTEST_API ValueMismatchTestException : public std::exception
{
public:
    ValueMismatchTestException(const QString& expected, const QString& actual, const std::source_location& sourceLocation);

    QString expectedValue;
    QString actualValue;
    std::source_location location;
};
