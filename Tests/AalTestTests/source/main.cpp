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
    TestSuite suite{};
    suite.add([]() 
        {
        // do nothing
        });
    suite.run();

    assert(expectedPasses == suite.passedTests());
}

int main()
{
    RunExecutesTest();
    TestCanPass();

    return 0;
}
