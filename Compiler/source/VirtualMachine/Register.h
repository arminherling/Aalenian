#pragma once

#include <Defines.h>

struct COMPILER_API Register
{
    Register(u16 value) 
        : index{ value } 
    {}

    u16 index;
};
