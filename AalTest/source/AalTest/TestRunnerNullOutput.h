#pragma once

#include <AalTest/Asserts.h>
#include <AalTest/TestRunnerOutputBase.h>

class TestRunnerNullOutput : public TestRunnerOutputBase
{
public:
    TestRunnerNullOutput() = default;

    void writeSuiteName(const QString& name) override {};
    QPoint writeTestHeader(int currentTest, int totalTests, const QString& testName) override { return QPoint(); };
    QPoint writeSubTestHeader(int indentation, int currentTest, int totalTests, const QString& parameters) override { return QPoint(); };
    void updateTestResult(const QPoint& position, TestResult result, const std::chrono::nanoseconds& duration) override {};
    void writeTestPassedMessage() override {};
    void writeTestSkippedMessage(SkipTestException& e) override {};
    void writeTestFailedMessage(FailedTestException& e) override {};
    void writeTestValueMismatchMessage(ValueMismatchTestException& e) override {};
    void writeTestRunnerResult(const TestSuiteResult& result) override {};
    void writeTestRunnerTotalResult(const QList<TestSuiteResult>& results) override {};
    void writeEmptyLine() override {};
};