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
    m_output->writeEmptyLine();
    m_output->writeTestRunnerTotalResult(results);
}

TestSuiteResult TestRunner::runInternal(const TestSuite& suite)
{
    auto tests = suite.tests();
    auto currentTest = 1;
    auto totalTestCount = 0;
    for (const auto& test : tests)
    {
        totalTestCount += test->testCount();
    }
    auto totalCountString = QString::number(totalTestCount);

    m_output->writeSuiteName(suite.name());
    auto suiteStartTime = std::chrono::high_resolution_clock::now();

    for (const auto& test : tests)
    {
        auto resultPosition = test->writeHeader(m_output, currentTest, totalTestCount);
        test->run(m_output, totalCountString.length(), currentTest);
        test->writeResult(m_output, resultPosition);
    }

    auto suiteEndTime = std::chrono::high_resolution_clock::now();
    auto suiteDuration = suiteEndTime - suiteStartTime;

    return { suite.passedTests(), suite.skippedTests(), suite.failedTests(), totalTestCount, suiteDuration };
}
