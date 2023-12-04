#pragma once

#include <Defines.h>

#include <variant>

struct COMPILER_API Value
{
    Value();
    Value(bool value);
    Value(i32 value);

    bool isBool();
    bool isInt32();

    bool asBool();
    i32 asInt32();

    std::variant<bool, i32> data;
};
