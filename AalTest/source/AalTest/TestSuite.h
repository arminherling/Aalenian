#pragma once

#include <AalTest/API.h>
#include <AalTest/Exceptions.h>
#include <AalTest/TestResult.h>
#include <AalTest/TestRunnerOutputBase.h>
#include <functional>
#include <memory>
#include <QString>
#include <vector>

class TestBase
{
public:
    virtual TestResult run(const std::unique_ptr<TestRunnerOutputBase>& output, int headerIndentation) = 0;
    virtual const QString& testName() const = 0;
    TestResult result() { return m_result; }
    void setResult(TestResult result) { m_result = result; }

private:
    TestResult m_result = TestResult::Invalid;
};

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
        catch (FailTestException& e)
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
            catch (FailTestException& e)
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


class AALTEST_API TestSuite
{
public:
    TestSuite(const QString& name = __builtin_FUNCTION());

    template<typename TFunction>
    void add(const QString& testName, TFunction&& testFunction)
    {
        auto test = std::make_shared<
            SimpleTest <
            decltype(std::function(std::forward<TFunction>(testFunction)))>>(
                std::function(std::forward<TFunction>(testFunction)),
                testName);

        m_tests.push_back(test);
    }

    template<typename TFunction, typename TData>
    void add(const QString& testName, TFunction&& function, TData&& data)
    {
        auto test = std::make_shared<
            ParameterizedTest<
            decltype(std::function(std::forward<TFunction>(function))),
            decltype(std::function(std::forward<TData>(data)))::result_type>>(
                std::function(std::forward<TFunction>(function)),
                std::function(std::forward<TData>(data))(),
                testName);

        m_tests.push_back(test);
    }

    const QString& name() const { return m_name; }
    const std::vector<std::shared_ptr<TestBase>>& tests() const { return m_tests; }

    int passedTests() const
    {
        return std::count_if(begin(m_tests), end(m_tests), [](auto test) { return test->result() == TestResult::Passed; });
    }

    int failedTests() const
    {
        return std::count_if(begin(m_tests), end(m_tests), [](auto test) { return test->result() == TestResult::Failed; });
    }

    int skippedTests() const
    {
        return std::count_if(begin(m_tests), end(m_tests), [](auto test) { return test->result() == TestResult::Skipped; });
    }

private:
    QString m_name;
    std::vector<std::shared_ptr<TestBase>> m_tests;
};
