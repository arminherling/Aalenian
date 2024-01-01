#pragma once

#include <AalTest/Asserts.h>
#include <AalTest/TestSuite.h>
#include <AalTest/TestSuiteResult.h>
#include <QList>
#include <QPoint>

class TestRunnerOutputBase
{
public:
    virtual void writeSuiteName(const QString& name) = 0;
    virtual QPoint writeTestHeader(int currentTest, int totalTests, const QString& testName) = 0;
    virtual void updateTestResult(const QPoint& position, TestResult result) = 0;
    virtual void writeTestPassedMessage() = 0;
    virtual void writeTestSkippedMessage(SkipTestException& e) = 0;
    virtual void writeTestFailedMessage(FailTestException& e) = 0;
    virtual void writeTestValueMismatchMessage(ValueMismatchTestException& e) = 0;
    virtual void writeTestRunnerResult(const TestSuiteResult& result) = 0;
    virtual void writeTestRunnerTotalResult(const QList<TestSuiteResult>& results) = 0;
    virtual void writeEmptyLine() = 0;
};
