#pragma once

#include <AalTest/API.h>
#include <AalTest/TestSuite.h>
#include <AalTest/TestRunnerOutputBase.h>

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

private:
    std::unique_ptr<TestRunnerOutputBase> m_output;
};
