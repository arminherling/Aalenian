#pragma once

#include <API.h>
#include <TypeDefs.h>

struct COMPILER_API Value
{
    enum class Type
    {
        Invalid,
        Bool,
        I32
    };

    Value();
    Value(bool value);
    Value(i32 value);

    Type type{};
    union
    {
        bool boolean;
        i32 numI32;
    } as;
};
