#pragma once

#include <exception>
#include <QString>
#include <source_location>

class FailTestException : public std::exception
{
public:
    FailTestException(const std::source_location& sourceLocation);

    std::source_location location;
};

class SkipTestException : public std::exception
{
public:
    SkipTestException(const std::source_location& sourceLocation);

    std::source_location location;
};

class ValueMismatchTestException : public std::exception
{
public:
    ValueMismatchTestException(const QString& expected, const QString& actual, const std::source_location& sourceLocation);

    QString expectedValue;
    QString actualValue;
    std::source_location location;
};
