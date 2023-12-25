#pragma once

#include <exception>

class FailException : public std::exception
{
public:
    FailException() = default;
};
