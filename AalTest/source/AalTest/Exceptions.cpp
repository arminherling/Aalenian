#include "Exceptions.h"

ValueMismatchTestException::ValueMismatchTestException(
    const QString& expected,
    const QString& actual)
    : expectedValue{ expected }
    , actualValue{ actual }
{
}
