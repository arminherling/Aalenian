#pragma once

#include <AalTest/API.h>
#include "Exceptions.h"

namespace AalTest 
{
    AALTEST_API void Fail();
    AALTEST_API void Skip();
    AALTEST_API void IsTrue(bool value);
    AALTEST_API void IsFalse(bool value);
    
    template<typename T>
    void AreEqual(T expectedValue, T actualValue)
    {
        if (expectedValue != actualValue)
            throw ValueMismatchTestException();
    };
}
