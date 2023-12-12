#pragma once

#include <Defines.h>

struct CallFrame
{
    u16 returnAddress;
    u16 baseRegister;
};
