#pragma once

#include <AalTest/Asserts.h>
#include <AalTest/TestRunnerOutputBase.h>

class TestRunnerNullOutput : public TestRunnerOutputBase
{
public:
    TestRunnerNullOutput() = default;

    void writeSuiteName(const QString& name) override {};
    QPoint writeTestHeader(int currentTest, int totalTests, const QString& testName, bool hasSubTests) override { return QPoint(); };
    QPoint writeSubTestHeader(int indentation, int currentTest, int totalTests, const QString& parameters) override { return QPoint(); };
    void updateTestResult(const QPoint& position, TestResultKind result) override {};
    void writeTestPassedMessage() override {};
    void writeTestSkippedMessage(SkipTestException& e) override {};
    void writeTestFailedMessage(FailedTestException& e) override {};
    void writeTestValueMismatchMessage(ValueMismatchTestException& e) override {};
    void writeTestRunnerResult(const TestSuiteResult& result) override {};
    void writeTestRunnerTotalResult(const QList<TestSuiteResult>& results) override {};
    void writeEmptyLine() override {};
};
