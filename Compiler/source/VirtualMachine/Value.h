#pragma once

#include <API.h>
#include <TypeDefs.h>

struct COMPILER_API Value
{
    enum class Type
    {
        Invalid,
        I32
    };

    Value();
    Value(i32 value);

    Type type{};
    union
    {
        i32 numI32;
    } as;
};
