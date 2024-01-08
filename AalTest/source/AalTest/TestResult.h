#pragma once

#include <QList>

enum class TestResultKind
{
    Invalid,
    Skipped,
    Failed,
    Passed
};

struct TestResult
{
    QList<TestResultKind> data;
};
