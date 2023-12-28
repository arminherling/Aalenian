#pragma once

#include <AalTest/API.h>

namespace AalTest 
{
    AALTEST_API void Fail();
    AALTEST_API void Skip();
    AALTEST_API void IsTrue(bool value);
    AALTEST_API void IsFalse(bool value);
    AALTEST_API void AreEqual(bool expectedValue, bool actualValue);
}
