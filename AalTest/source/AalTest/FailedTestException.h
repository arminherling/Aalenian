#pragma once

#include <exception>
#include <source_location>

class FailedTestException : public std::exception
{
public:
    FailedTestException(const std::source_location& sourceLocation);

    std::source_location location;
};
