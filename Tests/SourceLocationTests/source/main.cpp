#include <AalTest.h>
#include "SourceLocationTests.h"

int main()
{
    TestRunner runner{};
    auto testSuite = SourceLocationTests();

    runner.run(testSuite);

    return 0;
}
