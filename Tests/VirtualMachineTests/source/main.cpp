#include <AalTest.h>
#include "VirtualMachineTests.h"

int main()
{
    TestRunner runner{};
    auto testSuites = VirtualMachineTestsSuite();

    runner.run(testSuites);

    return 0;
}
