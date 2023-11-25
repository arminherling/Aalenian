#pragma once

#include <API.h>
#include <TypeDefs.h>
#include <VirtualMachine/Register.h>

#include <vector>

enum Op : u8
{
    LoadInt32,
    AddInt32,
    Halt
};

class COMPILER_API ByteCode
{
public:
    ByteCode() = default;
    
    void writeLoadInt32(Register reg, i32 value);
    void writeAddInt32(Register target, Register rhs, Register lhs);
    void writeHalt();

    u8 readUInt8();
    u16 readUInt16();
    i32 readInt32();

private:
    i32 m_ip = 0;
    std::vector<u8> m_byteCode;

    inline void writeUInt8(u8 value);
    inline void writeUInt16(u16 value);
    inline void writeInt32(i32 value);
};