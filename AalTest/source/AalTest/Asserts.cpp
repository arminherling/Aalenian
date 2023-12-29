#include "Asserts.h"

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
