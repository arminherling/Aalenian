#include "ValueMismatchTestException.h"

ValueMismatchTestException::ValueMismatchTestException(
    const QString& expected,
    const QString& actual,
    const std::source_location& sourceLocation)
    : expectedValue{ expected }
    , actualValue{ actual }
    , location{ sourceLocation }
{
}
