#pragma once

#include <AalTest/API.h>
#include <AalTest/TestSuite.h>

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
    bool m_output;
};
