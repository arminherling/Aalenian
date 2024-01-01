#pragma once

#include <exception>
#include <source_location>

class SkipTestException : public std::exception
{
public:
    SkipTestException(const std::source_location& sourceLocation);

    std::source_location location;
};
