#pragma once

#include <AalTest/TestResult.h>
#include <AalTest/TestRunnerOutputBase.h>
#include <QString>

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
