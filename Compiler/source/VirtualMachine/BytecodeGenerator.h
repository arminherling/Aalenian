#pragma once

#include <API.h>
#include <TypeDefs.h>
#include <VirtualMachine/ByteCode.h>
#include <VirtualMachine/Register.h>

#include <vector>

class COMPILER_API BytecodeGenerator
{
public:
    BytecodeGenerator();

    //Register generateRegister();
    ByteCode result();

private:
    u16 m_stackPointer;
};

