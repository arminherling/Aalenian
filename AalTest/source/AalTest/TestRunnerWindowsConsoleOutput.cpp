#include "TestRunnerWindowsConsoleOutput.h"

#include <qdebug.h>

namespace
{
    QString TestNumber(int currentNumber, int totalCount)
    {
        auto totalCountString = QString::number(totalCount);
        auto countCharCount = totalCountString.length();
        auto numberString = QString::number(currentNumber);

        return QString("%1/%2").arg(numberString.rightJustified(countCharCount, ' '), totalCountString);
    }

    QString StringifyTestResult(TestResult result, bool colorize)
    {
        if (colorize)
        {
            switch (result)
            {
                case TestResult::Invalid:
                    return QString("Invalid");
                case TestResult::Skipped:
                    return QString("\033[38;2;255;228;160mSKIP\033[0m");
                case TestResult::Failed:
                    return QString("\033[38;2;244;75;86mFAIL\033[0m");
                case TestResult::Passed:
                    return QString("\033[38;2;138;226;138mPASS\033[0m");
            }
        }
        else
        {
            switch (result)
            {
                case TestResult::Invalid:
                    return QString("Invalid");
                case TestResult::Skipped:
                    return QString("SKIP");
                case TestResult::Failed:
                    return QString("FAIL");
                case TestResult::Passed:
                    return QString("PASS");
            }
        }
    }
}

void TestRunnerWindowsConsoleOutput::writeSuiteName(const QString& name)
{
    if (!name.isEmpty())
        qDebug().noquote() << QString("    --== %1 ==--").arg(name);
}

void TestRunnerWindowsConsoleOutput::writeTestResult(int currentTest, int totalTests, const QString& testName, TestResult result)
{
    qDebug().noquote()
        << TestNumber(currentTest, totalTests)
        << testName.leftJustified(50, ' ')
        << StringifyTestResult(result, true);
}

void TestRunnerWindowsConsoleOutput::writeTestPassedMessage()
{
}

void TestRunnerWindowsConsoleOutput::writeTestSkippedMessage(SkipTestException& e)
{
}

void TestRunnerWindowsConsoleOutput::writeTestFailedMessage(FailTestException& e)
{
}

void TestRunnerWindowsConsoleOutput::writeTestValueMismatchMessage(ValueMismatchTestException& e)
{
    qDebug() << "   Expected:" << true;
    qDebug() << "   But got: " << false;
}

void TestRunnerWindowsConsoleOutput::writeTestRunnerResult(int passedTests, int skippedTests, int failedTests, int totalTestCount)
{
    auto resultOutput = qDebug().noquote();

    resultOutput << QString("%1:").arg(StringifyTestResult(TestResult::Passed, true)) << TestNumber(passedTests, totalTestCount);
    resultOutput << QString("%1:").arg(StringifyTestResult(TestResult::Skipped, true)) << TestNumber(skippedTests, totalTestCount);
    resultOutput << QString("%1:").arg(StringifyTestResult(TestResult::Failed, true)) << TestNumber(failedTests, totalTestCount);
}
