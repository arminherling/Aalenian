#include <AalTest.h>

void RunExecutesTest()
{
    TestSuite suite{};
    int i = 0;
    suite.add([&i]() {i++; });

    suite.run();

    assert(i == 1);
}

void TestCanPass()
{
    int expectedPasses = 1;
    int expectedFails = 0;
    int expectedSkips = 0;
    TestSuite suite{};

    suite.add([]() 
        {
        // do nothing
        });
    suite.run();

    assert(expectedPasses == suite.passedTests());
    assert(expectedFails == suite.failedTests());
    assert(expectedSkips == suite.skippedTests());
}

void TestCanFail()
{
    int expectedPasses = 0;
    int expectedFails = 1;
    int expectedSkips = 0;
    TestSuite suite{};

    suite.add([]()
        {
            AalFail();
        });
    suite.run();

    assert(expectedPasses == suite.passedTests());
    assert(expectedFails == suite.failedTests());
    assert(expectedSkips == suite.skippedTests());
}

void TestCanBeSkipped()
{
    int expectedPasses = 0;
    int expectedFails = 0;
    int expectedSkips = 1;
    TestSuite suite{};

    suite.add([]()
        {
            AalSkip();
        });
    suite.run();

    assert(expectedPasses == suite.passedTests());
    assert(expectedFails == suite.failedTests());
    assert(expectedSkips == suite.skippedTests());
}

void TestSuitesReturnsAddedTests()
{
    int expectedTestCount = 2;
    TestSuite suite{};
    suite.add([]()
        {
            AalSkip();
        });
    suite.add([]()
        {
            AalFail();
        });

    assert(expectedTestCount == suite.tests().size());
}

int main()
{
    RunExecutesTest();
    TestCanPass();
    TestCanFail();
    TestCanBeSkipped();
    TestSuitesReturnsAddedTests();

    return 0;
}
