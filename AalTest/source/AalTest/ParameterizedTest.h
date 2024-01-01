#pragma once

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

        for (const auto& tuple : m_data)
        {
            QPoint resultPosition;
            try
            {
                resultPosition = output->writeSubTestHeader(headerIndentation, currentTest, totalSubTestCount);

                std::apply(m_function, tuple);

                output->updateTestResult(resultPosition, TestResult::Passed);
                output->writeTestPassedMessage();
            }
            catch (SkipTestException& e)
            {
                output->updateTestResult(resultPosition, TestResult::Skipped);
                output->writeTestSkippedMessage(e);
            }
            catch (FailedTestException& e)
            {
                output->updateTestResult(resultPosition, TestResult::Failed);
                output->writeTestFailedMessage(e);
                testResult = TestResult::Failed;
            }
            catch (ValueMismatchTestException& e)
            {
                output->updateTestResult(resultPosition, TestResult::Failed);
                output->writeTestValueMismatchMessage(e);
                testResult = TestResult::Failed;
            }
        }

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
