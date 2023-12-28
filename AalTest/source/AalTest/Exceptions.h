#pragma once

#include <exception>

class FailTestException : public std::exception
{
public:
    FailTestException() = default;
};

class SkipTestException : public std::exception
{
public:
    SkipTestException() = default;
};

class ValueMismatchTestException : public std::exception
{
public:
    ValueMismatchTestException() = default;
};
