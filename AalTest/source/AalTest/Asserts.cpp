#include "Asserts.h"
#include "Exceptions.h"

void AalFail()
{
    throw FailTestException();
}

void AalSkip()
{
    throw SkipTestException();
}
