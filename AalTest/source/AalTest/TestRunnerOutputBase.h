#pragma once

#include <AalTest/FailedTestException.h>
#include <AalTest/SkipTestException.h>
#include <AalTest/TestResult.h>
#include <AalTest/TestSuiteResult.h>
#include <AalTest/ValueMismatchTestException.h>
#include <QList>
#include <QPoint>

class TestRunnerOutputBase
{
public:
    virtual void writeSuiteName(const QString& name) = 0;
    virtual QPoint writeTestHeader(int currentTest, int totalTests, const QString& testName, bool hasSubTests) = 0;
    virtual QPoint writeSubTestHeader(int indentation, int currentTest, int totalTests, const QString& parameters) = 0;
    virtual void updateTestResult(const QPoint& position, TestResultKind result) = 0;
    virtual void writeTestPassedMessage() = 0;
    virtual void writeTestSkippedMessage(SkipTestException& e) = 0;
    virtual void writeTestFailedMessage(FailedTestException& e) = 0;
    virtual void writeTestValueMismatchMessage(ValueMismatchTestException& e) = 0;
    virtual void writeTestRunnerResult(const TestSuiteResult& result) = 0;
    virtual void writeTestRunnerTotalResult(const QList<TestSuiteResult>& results) = 0;
    virtual void writeEmptyLine() = 0;
};
