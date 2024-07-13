#pragma once

#include <Defines.h>
#include <Compiler/API.h>

struct COMPILER_API Label
{
    explicit Label(u16 value);

    u16 index;
};
