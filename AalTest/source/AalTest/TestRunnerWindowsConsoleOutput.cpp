#include "TestRunnerWindowsConsoleOutput.h"
#include <iostream>
#include <Windows.h>

namespace
{
    std::string TestNumber(int currentNumber, int totalCount)
    {
        auto totalCountString = QString::number(totalCount);
        auto countCharCount = totalCountString.length();
        auto numberString = QString::number(currentNumber);

        return QString("%1/%2").arg(numberString.rightJustified(countCharCount, ' '), totalCountString).toStdString();
    }

    std::string ResultNumber(int currentNumber, int totalCount)
    {
        auto totalCountString = QString::number(totalCount);
        auto numberString = QString::number(currentNumber);

        return QString("%1/%2").arg(numberString, totalCountString).toStdString();
    }

    QString StringifyTestResult(TestResult result, bool colorize)
    {
        if (colorize)
        {
            switch (result)
            {
                case TestResult::Skipped:
                    return QString("\033[38;2;255;228;160mSKIP\033[0m");
                case TestResult::Failed:
                    return QString("\033[38;2;244;75;86mFAIL\033[0m");
                case TestResult::Passed:
                    return QString("\033[38;2;138;226;138mPASS\033[0m");
                case TestResult::Invalid:
                default:
                    return QString("....");
            }
        }
        else
        {
            switch (result)
            {
                case TestResult::Skipped:
                    return QString("SKIP");
                case TestResult::Failed:
                    return QString("FAIL");
                case TestResult::Passed:
                    return QString("PASS");
                case TestResult::Invalid:
                default:
                    return QString("....");
            }
        }
    }
}

TestRunnerWindowsConsoleOutput::TestRunnerWindowsConsoleOutput()
    : m_consoleHandle{ GetStdHandle(STD_OUTPUT_HANDLE) }
    , m_oldConsoleOutputCodePage{ GetConsoleOutputCP() }
    , m_headerSize{ 70 }
{
    SetConsoleOutputCP(CP_UTF8);
}

void TestRunnerWindowsConsoleOutput::writeSuiteName(const QString& name)
{
    if (name.isEmpty())
        return;

    std::cout << "         --== " << name.toStdString() << " ==--" << std::endl;
}

QPoint TestRunnerWindowsConsoleOutput::writeTestHeader(int currentTest, int totalTests, const QString& testName)
{
    std::cout << " " << TestNumber(currentTest, totalTests) << " " << testName.leftJustified(m_headerSize, '.').toStdString() << " " << std::flush;

    CONSOLE_SCREEN_BUFFER_INFO screenBuffer;
    GetConsoleScreenBufferInfo(m_consoleHandle, &screenBuffer);
    int x = screenBuffer.dwCursorPosition.X;
    int y = screenBuffer.dwCursorPosition.Y;

    std::cout << "...." << std::endl;

    return { x, y };
}

QPoint TestRunnerWindowsConsoleOutput::writeSubTestHeader(int indentation, int currentTest, int totalTests)
{
    auto indent = QString(" ").repeated(1 + indentation).toStdString();
    auto testNumber = TestNumber(currentTest, totalTests);
    auto testNumberSize = testNumber.size();

    auto testAndSubTestSizeDifference = testNumberSize - indentation;
    auto headerSize = m_headerSize - indentation - testAndSubTestSizeDifference;

    std::cout << indent << testNumber << " " << QString().leftJustified(headerSize, '.').toStdString() << " " << std::flush;

    CONSOLE_SCREEN_BUFFER_INFO screenBuffer;
    GetConsoleScreenBufferInfo(m_consoleHandle, &screenBuffer);
    int x = screenBuffer.dwCursorPosition.X;
    int y = screenBuffer.dwCursorPosition.Y;

    std::cout << "...." << std::endl;

    return { x, y };
}

void TestRunnerWindowsConsoleOutput::updateTestResult(const QPoint& position, TestResult result)
{
    std::cout << std::flush;

    CONSOLE_SCREEN_BUFFER_INFO screenBuffer;
    GetConsoleScreenBufferInfo(m_consoleHandle, &screenBuffer);
    int oldX = screenBuffer.dwCursorPosition.X;
    int oldY = screenBuffer.dwCursorPosition.Y;

    COORD cursorPosition;
    cursorPosition.X = position.x();
    cursorPosition.Y = position.y();
    SetConsoleCursorPosition(m_consoleHandle, cursorPosition);

    std::cout << StringifyTestResult(result, true).toStdString() << std::flush;

    cursorPosition.X = oldX;
    cursorPosition.Y = oldY;
    SetConsoleCursorPosition(m_consoleHandle, cursorPosition);
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
    std::cout << " " << e.location.file_name() << " Line:" << e.location.line() << std::endl;

    std::cout << "   Expected: " << e.expectedValue.toStdString() << std::endl;
    std::cout << "   But got:  " << e.actualValue.toStdString() << std::endl;
}

void TestRunnerWindowsConsoleOutput::writeTestRunnerResult(const TestSuiteResult& result)
{
    std::cout
        << " " << StringifyTestResult(TestResult::Passed, true).toStdString()
        << " " << ResultNumber(result.passedTestCount, result.totalTestCount)
        << " " << StringifyTestResult(TestResult::Skipped, true).toStdString()
        << " " << ResultNumber(result.skippedTestCount, result.totalTestCount)
        << " " << StringifyTestResult(TestResult::Failed, true).toStdString()
        << " " << ResultNumber(result.failedTestCount, result.totalTestCount) << std::endl;
}

void TestRunnerWindowsConsoleOutput::writeTestRunnerTotalResult(const QList<TestSuiteResult>& results)
{
    TestSuiteResult totalResult{};
    for (const auto& result : results)
    {
        totalResult.passedTestCount += result.passedTestCount;
        totalResult.skippedTestCount += result.skippedTestCount;
        totalResult.failedTestCount += result.failedTestCount;
        totalResult.totalTestCount += result.totalTestCount;
    }

    std::cout << "         ==== Total Result ==== " << std::endl;
    writeTestRunnerResult(totalResult);
}

void TestRunnerWindowsConsoleOutput::writeEmptyLine()
{
    std::cout << std::endl;
}
