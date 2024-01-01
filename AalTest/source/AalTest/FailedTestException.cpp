#include "FailedTestException.h"

FailedTestException::FailedTestException(const std::source_location& sourceLocation)
    : location{ sourceLocation }
{
}
