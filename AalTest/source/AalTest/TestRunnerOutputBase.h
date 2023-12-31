#pragma once

#include <AalTest/Asserts.h>
#include <AalTest/TestSuite.h>

class TestRunnerOutputBase
{
public:
    virtual void writeSuiteName(const QString& name) = 0;
    virtual void writeTestResult(int currentTest, int totalTests, const QString& testName, TestResult result) = 0;
    virtual void writeTestPassedMessage() = 0;
    virtual void writeTestSkippedMessage(SkipTestException& e) = 0;
    virtual void writeTestFailedMessage(FailTestException& e) = 0;
    virtual void writeTestValueMismatchMessage(ValueMismatchTestException& e) = 0;
    virtual void writeTestRunnerResult(int passedTests, int skippedTests, int failedTests, int totalTestCount) = 0;
};
