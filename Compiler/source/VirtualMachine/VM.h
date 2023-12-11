#pragma once

#include <Defines.h>
#include <VirtualMachine/ByteCode.h>
#include <VirtualMachine/Register.h>
#include <VirtualMachine/Value.h>

#include <vector>
#include <stack>

struct CallFrame
{
    u16 returnAddress;
    u16 baseRegister;
};

class COMPILER_API VM
{
public:
    VM();

    i32 run(ByteCode& instructions);
    Value getValue(Register);
    Value getRelativeValue(Register);

private:
    void setValue(Register, const Value&);
    void setRelativeValue(Register, const Value&);

    std::vector<Value> m_registers;
    std::stack<CallFrame> m_callFrames;
};
