#pragma once

#include <AalTest/TestResult.h>
#include <AalTest/TestRunnerOutputBase.h>
#include <QPoint>
#include <QString>

class TestBase
{
public:
    virtual QPoint writeHeader(const std::unique_ptr<TestRunnerOutputBase>& output, int currentTest, int totalTestCount) const = 0;
    virtual void run(const std::unique_ptr<TestRunnerOutputBase>& output, int headerIndentation, int& currentTest) = 0;
    virtual void writeResult(const std::unique_ptr<TestRunnerOutputBase>& output, const QPoint& position) const = 0;
    virtual const QString& testName() const = 0;
    virtual int testCount() const = 0;
    TestResult result() const { return m_result; }
    void addResult(TestResultKind result) { m_result.data.append(result); }

private:
    TestResult m_result;
};
