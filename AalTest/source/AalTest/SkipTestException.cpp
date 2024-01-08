#include "SkipTestException.h"

SkipTestException::SkipTestException(const std::source_location& sourceLocation)
    : location{ sourceLocation }
{
}
