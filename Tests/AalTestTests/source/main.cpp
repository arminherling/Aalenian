#include <AalTest.h>
#include "AalTestTests.h"

int main()
{
    TestRunner runner{};
    auto aalTestTestsSuite = AalTestTestsSuite();

    runner.run(aalTestTestsSuite);

    return 0;
}
