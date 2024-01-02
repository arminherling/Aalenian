#include <AalTest.h>
#include "ParserTests.h"

int main()
{
    TestRunner runner{};
    auto testSuites = ParserTestsSuite();

    runner.run(testSuites);

    return 0;
}
