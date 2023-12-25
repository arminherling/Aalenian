#include "Asserts.h"
#include "Exceptions.h"

void AalFail()
{
    throw FailException();
}
