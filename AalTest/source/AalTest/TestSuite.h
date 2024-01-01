#pragma once

#include <AalTest/API.h>
#include <AalTest/TestResult.h>
#include <AalTest/SimpleTest.h>
#include <AalTest/ParameterizedTest.h>
#include <functional>
#include <memory>
#include <QString>
#include <vector>

class AALTEST_API TestSuite
{
public:
    TestSuite(const QString& name = __builtin_FUNCTION());

    template<typename TFunction>
    void add(const QString& testName, TFunction&& testFunction)
    {
        auto test = std::make_shared<
            SimpleTest<
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
    const QList<std::shared_ptr<TestBase>>& tests() const { return m_tests; }

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
    QList<std::shared_ptr<TestBase>> m_tests;
};
