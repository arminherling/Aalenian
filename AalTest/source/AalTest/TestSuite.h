#pragma once

#include <AalTest/API.h>

#include <memory>
#include <functional>
#include <vector>

class TestBase
{
public:
    virtual void run() = 0;
};

template<typename TFunction>
class Test : public TestBase
{
public:
    Test(TFunction&& function)
        : m_function{ function }
    {
    }

    void run() override
    {
        m_function();
    }

private:
    TFunction m_function;
};

class AALTEST_API TestSuite
{
public:
    TestSuite();

    template<typename T>
    void add(T&& testFunction)
    {
        auto test = std::make_shared<
            Test<
            decltype(std::function(std::forward<T>(testFunction)))>>(
                std::function(std::forward<T>(testFunction)));

        m_tests.push_back(test);
    }

    void run()
    {
        for (const auto& test : m_tests)
        {
            test->run();
            m_passedTests++;
        }
    }

    int passedTests()
    {
        return m_passedTests;
    }

private:
    std::vector<std::shared_ptr<TestBase>> m_tests;
    int m_passedTests;
};
