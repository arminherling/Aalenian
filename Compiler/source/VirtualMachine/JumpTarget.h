#pragma once

#include <Defines.h>

struct COMPILER_API JumpTarget
{
    explicit JumpTarget(u16 value);

    u16 index;
};
