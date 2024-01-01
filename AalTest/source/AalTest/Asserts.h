#pragma once

#include <AalTest/API.h>
#include <source_location>
#include <QString>

namespace AalTest 
{
    AALTEST_API void Fail(const std::source_location& location = std::source_location::current());
    AALTEST_API void Skip(const std::source_location& location = std::source_location::current());
    AALTEST_API void IsTrue(bool value, const std::source_location& location = std::source_location::current());
    AALTEST_API void IsFalse(bool value, const std::source_location& location = std::source_location::current());
    
    AALTEST_API void AreEqual(bool expectedValue, bool actualValue, const std::source_location& location = std::source_location::current());
    AALTEST_API void AreEqual(int expectedValue, int actualValue, const std::source_location& location = std::source_location::current());
    AALTEST_API void AreEqual(const QString& expectedValue, const QString& actualValue, const std::source_location& location = std::source_location::current());
}
