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
    void writeTestRunnerResult(int passedTests, int skippedTests, int failedTests, int totalTestCount) override;

private:
    void* m_consoleHandle;
    unsigned int m_oldConsoleOutputCodePage;
};
