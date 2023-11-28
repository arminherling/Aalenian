#pragma once

#include <API.h>
#include <TypeDefs.h>
#include <VirtualMachine/ByteCode.h>
#include <VirtualMachine/Register.h>
#include <VirtualMachine/Value.h>

#include <vector>

class COMPILER_API VM
{
public:
    VM();

    i32 run(ByteCode& instructions);
    Value getValue(Register);

private:
    void setValue(Register, const Value&);

    std::vector<Value> m_registers;
};
