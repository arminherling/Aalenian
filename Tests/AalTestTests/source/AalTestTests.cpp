#include "AalTestTests.h"
#include <AalTest.h>

namespace
{
    void TestCanExecute()
    {
        TestRunner runner{ false };
        TestSuite suite{};
        int i = 0;
        suite.add(QString(), [&i]() {i++; });

        runner.run(suite);

        assert(i == 1);
    }

    void TestCanPass()
    {
        int expectedPasses = 1;
        int expectedFails = 0;
        int expectedSkips = 0;
        TestRunner runner{ false };
        TestSuite suite{};

        suite.add(QString(), []()
            {
                // do nothing
            });
        runner.run(suite);

        assert(expectedPasses == suite.passedTests());
        assert(expectedFails == suite.failedTests());
        assert(expectedSkips == suite.skippedTests());
    }

    void TestCanFail()
    {
        int expectedPasses = 0;
        int expectedFails = 1;
        int expectedSkips = 0;
        TestRunner runner{ false };
        TestSuite suite{};

        suite.add(QString(), []()
            {
                AalTest::Fail();
            });
        runner.run(suite);

        assert(expectedPasses == suite.passedTests());
        assert(expectedFails == suite.failedTests());
        assert(expectedSkips == suite.skippedTests());
    }

    void TestCanBeSkipped()
    {
        int expectedPasses = 0;
        int expectedFails = 0;
        int expectedSkips = 1;
        TestRunner runner{ false };
        TestSuite suite{};

        suite.add(QString(), []()
            {
                AalTest::Skip();
            });
        runner.run(suite);

        assert(expectedPasses == suite.passedTests());
        assert(expectedFails == suite.failedTests());
        assert(expectedSkips == suite.skippedTests());
    }

    void TestSuitesReturnsAddedTests()
    {
        int expectedTestCount = 2;
        TestSuite suite{};
        suite.add(QString(), []()
            {
                AalTest::Skip();
            });
        suite.add(QString(), []()
            {
                AalTest::Fail();
            });

        assert(expectedTestCount == suite.tests().size());
    }

    void TestContainsCallingTestName()
    {
        QString expectedName = QString("TestContainsCallingTestName");
        TestRunner runner{ false };
        TestSuite suite{};
        suite.add(QString("TestContainsCallingTestName"), []()
            {
                AalTest::Skip();
            });

        auto test = suite.tests().at(0);

        assert(expectedName == test->testName());
    }

    void TestIsTrueWhenTrue()
    {
        int expectedPasses = 1;
        int expectedFails = 0;
        int expectedSkips = 0;
        TestRunner runner{ false };
        TestSuite suite{};

        suite.add(QString(), []()
            {
                auto value = true;
                AalTest::IsTrue(value);
            });
        runner.run(suite);

        assert(expectedPasses == suite.passedTests());
        assert(expectedFails == suite.failedTests());
        assert(expectedSkips == suite.skippedTests());
    }

    void TestIsTrueWhenFalse()
    {
        int expectedPasses = 0;
        int expectedFails = 1;
        int expectedSkips = 0;
        TestRunner runner{ false };
        TestSuite suite{};

        suite.add(QString(), []()
            {
                auto value = false;
                AalTest::IsTrue(value);
            });
        runner.run(suite);

        assert(expectedPasses == suite.passedTests());
        assert(expectedFails == suite.failedTests());
        assert(expectedSkips == suite.skippedTests());
    }

    void TestIsFalseWhenFalse()
    {
        int expectedPasses = 1;
        int expectedFails = 0;
        int expectedSkips = 0;
        TestRunner runner{ false };
        TestSuite suite{};

        suite.add(QString(), []()
            {
                auto value = false;
                AalTest::IsFalse(value);
            });
        runner.run(suite);

        assert(expectedPasses == suite.passedTests());
        assert(expectedFails == suite.failedTests());
        assert(expectedSkips == suite.skippedTests());
    }

    void TestIsFalseWhenTrue()
    {
        int expectedPasses = 0;
        int expectedFails = 1;
        int expectedSkips = 0;
        TestRunner runner{ false };
        TestSuite suite{};

        suite.add(QString(), []()
            {
                auto value = true;
                AalTest::IsFalse(value);
            });
        runner.run(suite);

        assert(expectedPasses == suite.passedTests());
        assert(expectedFails == suite.failedTests());
        assert(expectedSkips == suite.skippedTests());
    }

    void TestAreEqualWhenTrueAndTrue()
    {
        int expectedPasses = 1;
        int expectedFails = 0;
        int expectedSkips = 0;
        TestRunner runner{ false };
        TestSuite suite{};

        suite.add(QString(), []()
            {
                auto expectedValue = true;
                auto actualValue = true;
                AalTest::AreEqual(expectedValue, actualValue);
            });
        runner.run(suite);

        assert(expectedPasses == suite.passedTests());
        assert(expectedFails == suite.failedTests());
        assert(expectedSkips == suite.skippedTests());
    }

    void TestAreEqualWhenFalseAndFalse()
    {
        int expectedPasses = 1;
        int expectedFails = 0;
        int expectedSkips = 0;
        TestRunner runner{ false };
        TestSuite suite{};

        suite.add(QString(), []()
            {
                auto expectedValue = false;
                auto actualValue = false;
                AalTest::AreEqual(expectedValue, actualValue);
            });
        runner.run(suite);

        assert(expectedPasses == suite.passedTests());
        assert(expectedFails == suite.failedTests());
        assert(expectedSkips == suite.skippedTests());
    }

    void TestAreEqualWhenTrueAndFalse()
    {
        int expectedPasses = 0;
        int expectedFails = 1;
        int expectedSkips = 0;
        TestRunner runner{ false };
        TestSuite suite{};

        suite.add(QString(), []()
            {
                auto expectedValue = true;
                auto actualValue = false;
                AalTest::AreEqual(expectedValue, actualValue);
            });
        runner.run(suite);

        assert(expectedPasses == suite.passedTests());
        assert(expectedFails == suite.failedTests());
        assert(expectedSkips == suite.skippedTests());
    }

    void TestAreEqualWhenZeroAndZero()
    {
        int expectedPasses = 1;
        int expectedFails = 0;
        int expectedSkips = 0;
        TestRunner runner{ false };
        TestSuite suite{};

        suite.add(QString(), []()
            {
                auto expectedValue = 0;
                auto actualValue = 0;
                AalTest::AreEqual(expectedValue, actualValue);
            });
        runner.run(suite);

        assert(expectedPasses == suite.passedTests());
        assert(expectedFails == suite.failedTests());
        assert(expectedSkips == suite.skippedTests());
    }

    void TestAreEqualWhenOneAndOne()
    {
        int expectedPasses = 1;
        int expectedFails = 0;
        int expectedSkips = 0;
        TestRunner runner{ false };
        TestSuite suite{};

        suite.add(QString(), []()
            {
                auto expectedValue = 1;
                auto actualValue = 1;
                AalTest::AreEqual(expectedValue, actualValue);
            });
        runner.run(suite);

        assert(expectedPasses == suite.passedTests());
        assert(expectedFails == suite.failedTests());
        assert(expectedSkips == suite.skippedTests());
    }

    void TestAreEqualWhenOneAndZero()
    {
        int expectedPasses = 0;
        int expectedFails = 1;
        int expectedSkips = 0;
        TestRunner runner{ false };
        TestSuite suite{};

        suite.add(QString(), []()
            {
                auto expectedValue = 1;
                auto actualValue = 0;
                AalTest::AreEqual(expectedValue, actualValue);
            });
        runner.run(suite);

        assert(expectedPasses == suite.passedTests());
        assert(expectedFails == suite.failedTests());
        assert(expectedSkips == suite.skippedTests());
    }

    void TestAreEqualWhenEmptyStringAndEmptyString()
    {
        int expectedPasses = 1;
        int expectedFails = 0;
        int expectedSkips = 0;
        TestRunner runner{ false };
        TestSuite suite{};

        suite.add(QString(), []()
            {
                auto expectedValue = QString();
                auto actualValue = QString();
                AalTest::AreEqual(expectedValue, actualValue);
            });
        runner.run(suite);

        assert(expectedPasses == suite.passedTests());
        assert(expectedFails == suite.failedTests());
        assert(expectedSkips == suite.skippedTests());
    }

    void TestAreEqualWhenStringAndSameString()
    {
        int expectedPasses = 1;
        int expectedFails = 0;
        int expectedSkips = 0;
        TestRunner runner{ false };
        TestSuite suite{};

        suite.add(QString(), []()
            {
                auto expectedValue = QString("string");
                auto actualValue = QString("string");
                AalTest::AreEqual(expectedValue, actualValue);
            });
        runner.run(suite);

        assert(expectedPasses == suite.passedTests());
        assert(expectedFails == suite.failedTests());
        assert(expectedSkips == suite.skippedTests());
    }

    void TestAreEqualWhenStringAndDifferentString()
    {
        int expectedPasses = 0;
        int expectedFails = 1;
        int expectedSkips = 0;
        TestRunner runner{ false };
        TestSuite suite{};

        suite.add(QString(), []()
            {
                auto expectedValue = QString("string");
                auto actualValue = QString("other");
                AalTest::AreEqual(expectedValue, actualValue);
            });
        runner.run(suite);

        assert(expectedPasses == suite.passedTests());
        assert(expectedFails == suite.failedTests());
        assert(expectedSkips == suite.skippedTests());
    }

    void TestRunnerExecutesTests()
    {
        TestRunner runner{ false };
        TestSuite suite{};
        suite.add(QString(), []()
            {
            });
        suite.add(QString(), []()
            {
                AalTest::Skip();
            });
        suite.add(QString(), []()
            {
                AalTest::Fail();
            });
        runner.run(suite);
    }

    // all tests with parameterized data

}

TestSuite AalTestTestsSuite()
{
    TestSuite suite{};
    suite.add(QString("TestCanExecute"), TestCanExecute);
    suite.add(QString("TestCanPass"), TestCanPass);
    suite.add(QString("TestCanFail"), TestCanFail);
    suite.add(QString("TestCanBeSkipped"), TestCanBeSkipped);
    suite.add(QString("TestSuitesReturnsAddedTests"), TestSuitesReturnsAddedTests);
    suite.add(QString("TestContainsCallingTestName"), TestContainsCallingTestName);
    suite.add(QString("TestIsTrueWhenTrue"), TestIsTrueWhenTrue);
    suite.add(QString("TestIsTrueWhenFalse"), TestIsTrueWhenFalse);
    suite.add(QString("TestIsFalseWhenFalse"), TestIsFalseWhenFalse);
    suite.add(QString("TestIsFalseWhenTrue"), TestIsFalseWhenTrue);
    suite.add(QString("TestAreEqualWhenTrueAndTrue"), TestAreEqualWhenTrueAndTrue);
    suite.add(QString("TestAreEqualWhenFalseAndFalse"), TestAreEqualWhenFalseAndFalse);
    suite.add(QString("TestAreEqualWhenTrueAndFalse"), TestAreEqualWhenTrueAndFalse);
    suite.add(QString("TestAreEqualWhenZeroAndZero"), TestAreEqualWhenZeroAndZero);
    suite.add(QString("TestAreEqualWhenOneAndOne"), TestAreEqualWhenOneAndOne);
    suite.add(QString("TestAreEqualWhenOneAndZero"), TestAreEqualWhenOneAndZero);
    suite.add(QString("TestAreEqualWhenEmptyStringAndEmptyString"), TestAreEqualWhenEmptyStringAndEmptyString);
    suite.add(QString("TestAreEqualWhenStringAndSameString"), TestAreEqualWhenStringAndSameString);
    suite.add(QString("TestAreEqualWhenStringAndDifferentString"), TestAreEqualWhenStringAndDifferentString);
    suite.add(QString("TestRunnerExecutesTests"), TestRunnerExecutesTests);

    return suite;
}
