#pragma once

#include <Defines.h>
#include <Compiler/API.h>

struct COMPILER_API JumpIndex
{
    explicit JumpIndex(u16 value);

    u16 index;
};
