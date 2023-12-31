#pragma once

#include <AalTest/API.h>
#include <exception>
#include <QString>

class FailTestException : public std::exception
{
public:
    FailTestException() = default;
};

class SkipTestException : public std::exception
{
public:
    SkipTestException() = default;
};

class AALTEST_API ValueMismatchTestException : public std::exception
{
public:
    ValueMismatchTestException(const QString& expected, const QString& actual);

    QString expectedValue;
    QString actualValue;
};
