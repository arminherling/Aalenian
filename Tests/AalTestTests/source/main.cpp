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
            AalTest::Fail();
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
            AalTest::Skip();
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
            AalTest::Skip();
        });
    suite.add([]()
        {
            AalTest::Fail();
        });

    assert(expectedTestCount == suite.tests().size());
}

void TestContainsCallingFunctionName()
{
    QString expectedName = QString("TestContainsCallingFunctionName");
    TestSuite suite{};
    suite.add([]()
        {
            AalTest::Skip();
        });

    auto test = suite.tests().at(0);

    assert(expectedName == test->functionName());
}

void TestPassesOnIsTrueWhenTrue()
{
    int expectedPasses = 1;
    int expectedFails = 0;
    int expectedSkips = 0;
    TestSuite suite{};

    suite.add([]()
        {
            auto value = true;
            AalTest::IsTrue(value);
        });
    suite.run();

    assert(expectedPasses == suite.passedTests());
    assert(expectedFails == suite.failedTests());
    assert(expectedSkips == suite.skippedTests());
}

void TestFailsOnIsTrueWhenFalse()
{
    int expectedPasses = 0;
    int expectedFails = 1;
    int expectedSkips = 0;
    TestSuite suite{};

    suite.add([]()
        {
            auto value = false;
            AalTest::IsTrue(value);
        });
    suite.run();

    assert(expectedPasses == suite.passedTests());
    assert(expectedFails == suite.failedTests());
    assert(expectedSkips == suite.skippedTests());
}

void TestPassesOnIsFalseWhenFalse()
{
    int expectedPasses = 1;
    int expectedFails = 0;
    int expectedSkips = 0;
    TestSuite suite{};

    suite.add([]()
        {
            auto value = false;
            AalTest::IsFalse(value);
        });
    suite.run();

    assert(expectedPasses == suite.passedTests());
    assert(expectedFails == suite.failedTests());
    assert(expectedSkips == suite.skippedTests());
}

void TestFailsOnIsFalseWhenTrue()
{
    int expectedPasses = 0;
    int expectedFails = 1;
    int expectedSkips = 0;
    TestSuite suite{};

    suite.add([]()
        {
            auto value = true;
            AalTest::IsFalse(value);
        });
    suite.run();

    assert(expectedPasses == suite.passedTests());
    assert(expectedFails == suite.failedTests());
    assert(expectedSkips == suite.skippedTests());
}

// test equal values

// all tests with parameterized data

int main()
{
    RunExecutesTest();
    TestCanPass();
    TestCanFail();
    TestCanBeSkipped();
    TestSuitesReturnsAddedTests();
    TestContainsCallingFunctionName();
    TestPassesOnIsTrueWhenTrue();
    TestFailsOnIsTrueWhenFalse();
    TestPassesOnIsFalseWhenFalse();
    TestFailsOnIsFalseWhenTrue();

    return 0;
}
