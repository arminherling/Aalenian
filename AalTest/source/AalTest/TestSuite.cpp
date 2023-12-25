#include "TestSuite.h"

TestSuite::TestSuite()
    : m_tests{}
    , m_passedTests{ 0 }
    , m_failedTests{ 0 }
    , m_skippedTests{ 0 }
{
}
