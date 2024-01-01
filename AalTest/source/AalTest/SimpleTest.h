#pragma once

#include <AalTest/TestBase.h>
#include <AalTest/TestResult.h>
#include <AalTest/TestRunnerOutputBase.h>
#include <memory>
#include <QString>

template<typename TFunction>
class SimpleTest : public TestBase
{
public:
    SimpleTest(TFunction&& function, const QString& testName)
        : m_function{ function }
        , m_testName{ testName }
    {
    }

    TestResult run(const std::unique_ptr<TestRunnerOutputBase>& output, int headerIndentation) override
    {
        try
        {
            m_function();

            setResult(TestResult::Passed);
            output->writeTestPassedMessage();
        }
        catch (SkipTestException& e)
        {
            setResult(TestResult::Skipped);
            output->writeTestSkippedMessage(e);
        }
        catch (FailedTestException& e)
        {
            setResult(TestResult::Failed);
            output->writeTestFailedMessage(e);
        }
        catch (ValueMismatchTestException& e)
        {
            setResult(TestResult::Failed);
            output->writeTestValueMismatchMessage(e);
        }

        return result();
    }

    const QString& testName() const override
    {
        return m_testName;
    }

private:
    TFunction m_function;
    QString m_testName;
};
