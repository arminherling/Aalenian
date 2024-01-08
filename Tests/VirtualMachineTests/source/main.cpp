#include <AalTest.h>
#include "VirtualMachineTests.h"

int main()
{
    TestRunner runner{};
    auto testSuites = VirtualMachineTests();

    runner.run(testSuites);

    return 0;
}
