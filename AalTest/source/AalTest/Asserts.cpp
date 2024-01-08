#include "Asserts.h"

#include <AalTest/FailedTestException.h>
#include <AalTest/SkipTestException.h>

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
        throw ValueMismatchTestException(Stringify(true), Stringify(value), location);
}

void AalTest::IsFalse(bool value, const std::source_location& location)
{
    if (value)
        throw ValueMismatchTestException(Stringify(false), Stringify(value), location);
}
