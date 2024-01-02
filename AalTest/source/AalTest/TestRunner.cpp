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
    auto totalTestCount = (int)tests.size();
    auto currentTest = 1;

    auto totalCountString = QString::number(totalTestCount);
    auto subTestIndentation = (totalCountString.length() * 2) + 1;

    m_output->writeSuiteName(suite.name());
    auto suiteStartTime = std::chrono::high_resolution_clock::now();

    for (const auto& test : tests)
    {
        auto resultPosition = m_output->writeTestHeader(currentTest, totalTestCount, test->testName());
        auto testStartTime = std::chrono::high_resolution_clock::now();

        auto result = test->run(m_output, subTestIndentation);

        auto testEndTime = std::chrono::high_resolution_clock::now();
        auto testDuration = testEndTime - testStartTime;

        m_output->updateTestResult(resultPosition, result, testDuration);
        currentTest++;
    }

    auto suiteEndTime = std::chrono::high_resolution_clock::now();
    auto suiteDuration = suiteEndTime - suiteStartTime;

    return { suite.passedTests(), suite.skippedTests(), suite.failedTests(), totalTestCount, suiteDuration };
}
