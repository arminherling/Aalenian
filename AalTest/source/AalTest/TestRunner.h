#pragma once

#include <AalTest/API.h>
#include <AalTest/TestSuite.h>

class AALTEST_API TestRunner
{
public:
    TestRunner(bool output = true);

    void run(const TestSuite& suite);
private:
    bool m_output;
};
