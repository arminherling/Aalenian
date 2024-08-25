#include <AalTest.h>
#include "SourceLocationTests.h"

int main()
{
    AalTest::TestRunner runner{};
    auto testSuite = SourceLocationTests();

    runner.run(testSuite);

    return 0;
}
