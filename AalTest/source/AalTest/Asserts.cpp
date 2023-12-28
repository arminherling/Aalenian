#include "Asserts.h"
#include "Exceptions.h"

void AalTest::Fail()
{
    throw FailTestException();
}

void AalTest::Skip()
{
    throw SkipTestException();
}

void AalTest::IsTrue(bool value)
{
    if (!value)
        throw ValueMismatchTestException();
}

void AalTest::IsFalse(bool value)
{
    IsTrue(!value);
}

void AalTest::AreEqual(bool expectedValue, bool actualValue)
{
    if (expectedValue != actualValue)
        throw ValueMismatchTestException();
}
