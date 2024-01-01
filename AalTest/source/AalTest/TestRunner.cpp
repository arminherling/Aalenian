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
    auto result = runInternal(suite);

    m_output->writeTestRunnerResult(result);
}

void TestRunner::run(const QList<TestSuite>& suites)
{
    QList<TestSuiteResult> results;
    for (const auto& suite : suites)
    {
        auto result = runInternal(suite);
        results << result;

        m_output->writeTestRunnerResult(result);
        m_output->writeEmptyLine();
    }

    m_output->writeTestRunnerTotalResult(results);
}

TestSuiteResult TestRunner::runInternal(const TestSuite& suite)
{
    auto tests = suite.tests();
    auto totalTestCount = (int)tests.size();
    auto currentTest = 1;

    m_output->writeSuiteName(suite.name());

    for (const auto& test : tests)
    {
        QPoint resultPosition;

        try
        {
            resultPosition = m_output->writeTestHeader(currentTest, totalTestCount, test->testName());

            test->run();
            test->setResult(TestResult::Passed);

            m_output->updateTestResult(resultPosition, test->result());
            m_output->writeTestPassedMessage();
        }
        catch (SkipTestException& e)
        {
            test->setResult(TestResult::Skipped);

            m_output->updateTestResult(resultPosition, test->result());
            m_output->writeTestSkippedMessage(e);
        }
        catch (FailTestException& e)
        {
            test->setResult(TestResult::Failed);

            m_output->updateTestResult(resultPosition, test->result());
            m_output->writeTestFailedMessage(e);
        }
        catch (ValueMismatchTestException& e)
        {
            test->setResult(TestResult::Failed);

            m_output->updateTestResult(resultPosition, test->result());
            m_output->writeTestValueMismatchMessage(e);
        }

        currentTest++;
    }

    return { suite.passedTests(), suite.skippedTests(), suite.failedTests(), totalTestCount };
}
