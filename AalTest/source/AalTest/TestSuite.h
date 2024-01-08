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
        auto passed = 0;
        for (const auto& test : m_tests)
        {
            for (const auto data : test->result().data)
            {
                if(data == TestResultKind::Passed)
                    passed++;
            }
        }
        return passed;
    }

    int failedTests() const
    {
        auto failed = 0;
        for (const auto& test : m_tests)
        {
            for (const auto data : test->result().data)
            {
                if (data == TestResultKind::Failed)
                    failed++;
            }
        }
        return failed;
    }

    int skippedTests() const
    {
        auto skipped = 0;
        for (const auto& test : m_tests)
        {
            for (const auto data : test->result().data)
            {
                if (data == TestResultKind::Skipped)
                    skipped++;
            }
        }
        return skipped;
    }

private:
    QString m_name;
    QList<std::shared_ptr<TestBase>> m_tests;
};
