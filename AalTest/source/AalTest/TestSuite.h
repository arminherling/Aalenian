#pragma once

#include <AalTest/API.h>
#include <AalTest/Exceptions.h>
#include <functional>
#include <memory>
#include <QString>
#include <vector>

enum class TestResult
{
    Invalid,
    Skipped,
    Failed,
    Passed
};

class TestBase
{
public:
    virtual void run() = 0;
    virtual const QString& testName() const = 0;
    TestResult result() { return m_result; }
    void setResult(TestResult result) { m_result = result; }

private:
    TestResult m_result = TestResult::Invalid;
};

template<typename TFunction>
class Test : public TestBase
{
public:
    Test(TFunction&& function, const QString& testName)
        : m_function{ function }
        , m_testName{ testName }
    {
    }

    void run() override
    {
        m_function();
    }

    const QString& testName() const override
    {
        return m_testName;
    }

private:
    TFunction m_function;
    QString m_testName;
};

class AALTEST_API TestSuite
{
public:
    TestSuite(const QString& name = __builtin_FUNCTION());

    template<typename T>
    void add(const QString& testName, T&& testFunction)
    {
        auto test = std::make_shared<
            Test<
            decltype(std::function(std::forward<T>(testFunction)))>>(
                std::function(std::forward<T>(testFunction)),
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
