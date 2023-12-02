#pragma once

#include <Defines.h>

struct COMPILER_API Value
{
    enum class Type
    {
        Invalid,
        Bool,
        Int32
    };

    Value();
    Value(bool value);
    Value(i32 value);

    Type type{};
    union
    {
        bool boolean;
        i32 int32;
    } as;
};
