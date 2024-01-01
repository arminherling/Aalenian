#include "Asserts.h"

#include <AalTest/FailedTestException.h>
#include <AalTest/SkipTestException.h>
#include <AalTest/ValueMismatchTestException.h>

namespace 
{
    QString stringify(bool value)
    {
        return value ? QString("true") : QString("false");
    }
}

void AalTest::Fail(const std::source_location& location)
{
    throw FailedTestException(location);
}

void AalTest::Skip(const std::source_location& location)
{
    throw SkipTestException(location);
}

void AalTest::IsTrue(bool value, const std::source_location& location)
{
    if (!value)
        throw ValueMismatchTestException(stringify(true), stringify(value), location);
}

void AalTest::IsFalse(bool value, const std::source_location& location)
{
    if (value)
        throw ValueMismatchTestException(stringify(false), stringify(value), location);
}

void AalTest::AreEqual(bool expectedValue, bool actualValue, const std::source_location& location)
{
    if (expectedValue != actualValue)
        throw ValueMismatchTestException(stringify(expectedValue), stringify(actualValue), location);
}

void AalTest::AreEqual(int expectedValue, int actualValue, const std::source_location& location)
{
    if (expectedValue != actualValue)
        throw ValueMismatchTestException(QString::number(expectedValue), QString::number(actualValue), location);
}

void AalTest::AreEqual(const QString& expectedValue, const QString& actualValue, const std::source_location& location)
{
    if (expectedValue != actualValue)
        throw ValueMismatchTestException(expectedValue, actualValue, location);
}
