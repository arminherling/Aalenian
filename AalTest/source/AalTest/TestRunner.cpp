#include "TestRunner.h"
#include <AalTest/TestRunnerNullOutput.h>
#include <AalTest/TestRunnerWindowsConsoleOutput.h>

namespace
{
    std::unique_ptr<TestRunnerOutputBase> CreateOutput(TestRunner::OutputMode output)
    {
        switch (output)
        {
            case TestRunner::OutputMode::Console:
                return std::make_unique<TestRunnerWindowsConsoleOutput>();
            case TestRunner::OutputMode::None:
            default:
                return std::make_unique<TestRunnerNullOutput>();
        }
    }
}

TestRunner::TestRunner(OutputMode output)
    : m_output{ CreateOutput(output) }
{
}

void TestRunner::run(const TestSuite& suite)
{
    auto suiteName = suite.name();
    auto tests = suite.tests();
    auto totalTestCount = tests.size();
    auto currentTest = 1;

    m_output->writeSuiteName(suiteName);

    for (const auto& test : tests)
    {
        try
        {
            test->run();
            test->setResult(TestResult::Passed);

            m_output->writeTestResult(currentTest, totalTestCount, test->testName(), test->result());
            m_output->writeTestPassedMessage();
        }
        catch (SkipTestException& e)
        {
            test->setResult(TestResult::Skipped);

            m_output->writeTestResult(currentTest, totalTestCount, test->testName(), test->result());
            m_output->writeTestSkippedMessage(e);
        }
        catch (FailTestException& e)
        {
            test->setResult(TestResult::Failed);

            m_output->writeTestResult(currentTest, totalTestCount, test->testName(), test->result());
            m_output->writeTestFailedMessage(e);
        }
        catch (ValueMismatchTestException& e)
        {
            test->setResult(TestResult::Failed);

            m_output->writeTestResult(currentTest, totalTestCount, test->testName(), test->result());
            m_output->writeTestValueMismatchMessage(e);
        }

        currentTest++;
    }

    m_output->writeTestRunnerResult(suite.passedTests(), suite.skippedTests(), suite.failedTests(), totalTestCount);
}
