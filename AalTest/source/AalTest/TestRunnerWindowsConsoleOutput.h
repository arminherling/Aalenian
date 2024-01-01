#pragma once

#include <AalTest/TestRunnerOutputBase.h>
#include <QString>

class TestRunnerWindowsConsoleOutput : public TestRunnerOutputBase
{
public:
    TestRunnerWindowsConsoleOutput();
    
    void writeSuiteName(const QString& name) override;
    QPoint writeTestHeader(int currentTest, int totalTests, const QString& testName) override;
    void updateTestResult(const QPoint& position, TestResult result) override;
    void writeTestPassedMessage() override;
    void writeTestSkippedMessage(SkipTestException& e) override;
    void writeTestFailedMessage(FailTestException& e) override;
    void writeTestValueMismatchMessage(ValueMismatchTestException& e) override;
    void writeTestRunnerResult(const TestSuiteResult& result) override;
    void writeTestRunnerTotalResult(const QList<TestSuiteResult>& results) override;
    void writeEmptyLine() override;

private:
    void* m_consoleHandle;
    unsigned int m_oldConsoleOutputCodePage;
};
