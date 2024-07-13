#pragma once

#include <Defines.h>
#include <Compiler/API.h>

struct COMPILER_API Register
{
    Register(u16 value);

    u16 index;
};
