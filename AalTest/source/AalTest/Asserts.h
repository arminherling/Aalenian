#pragma once

#include <AalTest/API.h>
#include <AalTest/Stringify.h>
#include <AalTest/ValueMismatchTestException.h>

#include <QString>

#include <source_location>

namespace AalTest 
{
    AALTEST_API void Fail(const std::source_location& location = std::source_location::current());
    AALTEST_API void Skip(const std::source_location& location = std::source_location::current());
    AALTEST_API void IsTrue(bool value, const std::source_location& location = std::source_location::current());
    AALTEST_API void IsFalse(bool value, const std::source_location& location = std::source_location::current());
    
    template<class T1, class T2>
    void AreEqual(T1&& expectedValue, T2&& actualValue, const std::source_location& location = std::source_location::current())
    {
        if (expectedValue != actualValue)
            throw ValueMismatchTestException(Stringify(expectedValue), Stringify(actualValue), location);
    }
}
