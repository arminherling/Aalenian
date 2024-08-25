#include <AalTest.h>
#include "VirtualMachineTests.h"

int main()
{
    AalTest::TestRunner runner{};
    auto testSuites = VirtualMachineTests();

    runner.run(testSuites);

    return 0;
}
