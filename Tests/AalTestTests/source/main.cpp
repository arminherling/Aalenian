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
    TestSuite suite{};
    suite.add([]() 
        {
        // do nothing
        });
    suite.run();

    assert(expectedPasses == suite.passedTests());
    assert(expectedFails == suite.failedTests());
}

void TestCanFail()
{
    int expectedPasses = 0;
    int expectedFails = 1;
    TestSuite suite{};
    suite.add([]()
        {
            AalFail();
        });
    suite.run();

    assert(expectedPasses == suite.passedTests());
    assert(expectedFails == suite.failedTests());
}

int main()
{
    RunExecutesTest();
    TestCanPass();
    TestCanFail();

    return 0;
}
