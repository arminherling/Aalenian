#pragma once

#include <API.h>
#include <TypeDefs.h>

struct COMPILER_API Register
{
    Register(u16 value) 
        : index{ value } 
    {}

    u16 index;
};
