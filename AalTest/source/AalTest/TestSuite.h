#pragma once

#include <AalTest/API.h>
#include <AalTest/Exceptions.h>
#include <functional>
#include <memory>
#include <QString>
#include <vector>

class TestBase
{
public:
    virtual void run() = 0;
    virtual const QString& functionName() const = 0;
};

template<typename TFunction>
class Test : public TestBase
{
public:
    Test(TFunction&& function, const QString& functionName)
        : m_function{ function }
        , m_functionName{ functionName }
    {
    }

    void run() override
    {
        m_function();
    }

    const QString& functionName() const override 
    { 
        return m_functionName;
    }

private:
    TFunction m_function;
    QString m_functionName;
};

class AALTEST_API TestSuite
{
public:
    TestSuite();

    template<typename T>
    void add(T&& testFunction, const QString& callingFunctionName = __builtin_FUNCTION())
    {
        auto test = std::make_shared<
            Test<
            decltype(std::function(std::forward<T>(testFunction)))>>(
                std::function(std::forward<T>(testFunction)),
                callingFunctionName);

        m_tests.push_back(test);
    }

    void run()
    {
        for (const auto& test : m_tests)
        {
            try
            {
                test->run();
                m_passedTests++;
            }
            catch (SkipTestException& e)
            {
                m_skippedTests++;
            }
            catch (ValueMismatchTestException& e)
            {
                m_failedTests++;
            }
            catch (FailTestException& e)
            {
                m_failedTests++;
            }
        }
    }

    int passedTests() const
    {
        return m_passedTests;
    }

    int failedTests() const
    {
        return m_failedTests;
    }

    int skippedTests() const
    {
        return m_skippedTests;
    }

    const std::vector<std::shared_ptr<TestBase>>& tests() const { return m_tests; }

private:
    std::vector<std::shared_ptr<TestBase>> m_tests;
    int m_passedTests;
    int m_failedTests;
    int m_skippedTests;
};
