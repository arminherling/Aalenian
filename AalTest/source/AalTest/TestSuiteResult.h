#pragma once

#include <chrono>

struct TestSuiteResult
{
    int passedTestCount;
    int skippedTestCount;
    int failedTestCount;
    int totalTestCount;
    std::chrono::nanoseconds duration;
};
