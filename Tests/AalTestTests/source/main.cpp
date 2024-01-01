#include <AalTest.h>
#include "AalTestTests.h"

int main()
{
    TestRunner runner{};
    auto testSuites = AalTestTestsSuite();

    runner.run(testSuites);

    return 0;
}
