#include "Exceptions.h"

FailTestException::FailTestException(const std::source_location& sourceLocation)
    : location{ sourceLocation }
{
}

SkipTestException::SkipTestException(const std::source_location& sourceLocation)
    : location{ sourceLocation }
{
}

ValueMismatchTestException::ValueMismatchTestException(
    const QString& expected,
    const QString& actual,
    const std::source_location& sourceLocation)
    : expectedValue{ expected }
    , actualValue{ actual }
    , location{ sourceLocation }
{
}
