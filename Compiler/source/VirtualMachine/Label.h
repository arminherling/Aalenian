#pragma once

#include <API.h>
#include <TypeDefs.h>

struct COMPILER_API Label
{
    Label(u16 value)
        : index{ value }
    {
    }

    u16 index;
};
