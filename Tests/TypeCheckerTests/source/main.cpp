#include <AalTest.h>
#include "TypeCheckerTests.h"

int main()
{
    TestRunner runner{};
    auto testSuites = TypeCheckerTestsSuite();

    runner.run(testSuites);

    return 0;
}
