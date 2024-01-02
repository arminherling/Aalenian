#pragma once

#include <AalTest/Stringify.h>
#include <AalTest/TestBase.h>
#include <AalTest/TestResult.h>
#include <AalTest/TestRunnerOutputBase.h>
#include <memory>
#include <QString>

template<typename TFunction, typename TData>
class ParameterizedTest : public TestBase
{
public:
    ParameterizedTest(TFunction&& function, TData&& data, const QString& testName)
        : m_function{ function }
        , m_testName{ testName }
        , m_data{ data }
    {
    }

    TestResult run(const std::unique_ptr<TestRunnerOutputBase>& output, int headerIndentation) override
    {
        auto totalSubTestCount = m_data.size();
        auto currentTest = 1;
        auto testResult = TestResult::Passed;
        if (totalSubTestCount == 0)
        {
            setResult(TestResult::Skipped);
            return TestResult::Skipped;
        }

        auto failCount = 0;
        auto skipCount = 0;

        for (const auto& tuple : m_data)
        {
            QPoint resultPosition;
            try
            {
                resultPosition = output->writeSubTestHeader(headerIndentation, currentTest, totalSubTestCount, Stringify(tuple));
                auto startTime = std::chrono::high_resolution_clock::now();

                std::apply(m_function, tuple);

                auto endTime = std::chrono::high_resolution_clock::now();
                auto testDuration = endTime - startTime;

                output->updateTestResult(resultPosition, TestResult::Passed, testDuration);
                output->writeTestPassedMessage();
            }
            catch (SkipTestException& e)
            {
                output->updateTestResult(resultPosition, TestResult::Skipped);
                output->writeTestSkippedMessage(e);
                skipCount++;
            }
            catch (FailedTestException& e)
            {
                output->updateTestResult(resultPosition, TestResult::Failed);
                output->writeTestFailedMessage(e);
                failCount++;
            }
            catch (ValueMismatchTestException& e)
            {
                output->updateTestResult(resultPosition, TestResult::Failed);
                output->writeTestValueMismatchMessage(e);
                failCount++;
            }
        }

        if (totalSubTestCount == skipCount)
            testResult = TestResult::Skipped;
        else if (failCount > 0)
            testResult = TestResult::Failed;

        setResult(testResult);
        return testResult;
    }

    const QString& testName() const override
    {
        return m_testName;
    }

private:
    TFunction m_function;
    TData m_data;
    QString m_testName;
};
