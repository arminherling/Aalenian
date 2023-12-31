#pragma once

#include <AalTest/TestRunnerOutputBase.h>

class TestRunnerNullOutput : public TestRunnerOutputBase
{
public:
    TestRunnerNullOutput() = default;

    void writeSuiteName(const QString& name) override {};
    void writeTestResult(int currentTest, int totalTests, const QString& testName, TestResult result) override {};
    void writeTestPassedMessage() override {};
    void writeTestSkippedMessage(SkipTestException& e) override {};
    void writeTestFailedMessage(FailTestException& e) override {};
    void writeTestValueMismatchMessage(ValueMismatchTestException& e) override {};
    void writeTestRunnerResult(int passedTests, int skippedTests, int failedTests, int totalTestCount) override {};
};
