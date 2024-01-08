#pragma once

#include <AalTest/API.h>
#include <AalTest/TestRunnerOutputBase.h>
#include <AalTest/TestSuite.h>
#include <AalTest/TestSuiteResult.h>
#include <QList>

class AALTEST_API TestRunner
{
public:
    enum class OutputMode
    {
        None,
        Console
    };

    TestRunner(OutputMode output = OutputMode::Console);

    void run(const TestSuite& suite);
    void run(const QList<TestSuite>& suites);

private:
    std::unique_ptr<TestRunnerOutputBase> m_output;

    TestSuiteResult runInternal(const TestSuite& suite);
};
