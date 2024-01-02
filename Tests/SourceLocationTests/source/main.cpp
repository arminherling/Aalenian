#include <AalTest.h>
#include "SourceLocationTests.h"

int main()
{
    TestRunner runner{};
    auto testSuite = SourceLocationTestsSuite();

    runner.run(testSuite);

    return 0;
}
