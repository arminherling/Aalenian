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
        throw ValueMismatchTestException(QString("true"), QString("value"));
}

void AalTest::IsFalse(bool value)
{
    if (value)
        throw ValueMismatchTestException(QString("false"), QString("value"));
}
