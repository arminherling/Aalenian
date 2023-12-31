#include "TestRunner.h"
#include <qdebug.h>

namespace
{
    QString TestNumber(int n, const QString& totalCountString)
    {
        auto countCharCount = totalCountString.length();
        auto numberString = QString::number(n);

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

    void WriteTestResult(int n, const QString& totalCountString, const std::shared_ptr<TestBase>& test)
    {
        qDebug().noquote()
            << TestNumber(n, totalCountString)
            << test->testName().leftJustified(50, ' ')
            << StringifyTestResult(test->result(), true);
    }
}

TestRunner::TestRunner(OutputMode output)
    : m_output{ output  == OutputMode::Console }
{
}

void TestRunner::run(const TestSuite& suite)
{
    auto suiteName = suite.name();
    auto tests = suite.tests();

    if (m_output && !suiteName.isEmpty())
        qDebug().noquote() << QString("    --== %1 ==--").arg(suiteName);

    auto totalCount = QString::number(tests.size());
    auto n = 1;

    for (const auto& test : tests)
    {
        try
        {
            test->run();
            test->setResult(TestResult::Passed);

            if (m_output)
                WriteTestResult(n, totalCount, test);
        }
        catch (SkipTestException& e)
        {
            test->setResult(TestResult::Skipped);
            if (m_output)
                WriteTestResult(n, totalCount, test);
        }
        catch (FailTestException& e)
        {
            test->setResult(TestResult::Failed);
            if (m_output)
                WriteTestResult(n, totalCount, test);
        }
        catch (ValueMismatchTestException& e)
        {
            test->setResult(TestResult::Failed);
            if (m_output)
            {
                WriteTestResult(n, totalCount, test);

                qDebug() << "   Expected:" << true;
                qDebug() << "   But got: " << false;
            }
        }

        n++;
    }
    if (m_output)
    {
        auto resultOutput = qDebug().noquote();

        resultOutput << QString("%1:").arg(StringifyTestResult(TestResult::Passed, true)) << TestNumber(suite.passedTests(), totalCount);
        resultOutput << QString("%1:").arg(StringifyTestResult(TestResult::Skipped, true)) << TestNumber(suite.skippedTests(), totalCount);
        resultOutput << QString("%1:").arg(StringifyTestResult(TestResult::Failed, true)) << TestNumber(suite.failedTests(), totalCount);
    }
}
