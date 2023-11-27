#pragma once

#include <API.h>
#include <TypeDefs.h>
#include <VirtualMachine/Register.h>

#include <vector>

enum Op : u8
{
    LoadBool,
    NotBool,
    EqualBool,
    NotEqualBool,
    LoadInt32,
    AddInt32,
    SubtractInt32,
    MultiplyInt32,
    DivideInt32,
    NegateInt32,
    EqualInt32,
    NotEqualInt32,
    GreaterInt32,
    GreaterOrEqualInt32,
    LessInt32,
    LessOrEqualInt32,
    Jump,
    Halt
};

class COMPILER_API ByteCode
{
public:
    ByteCode() = default;
    
    void writeLoadBool(Register reg, bool value);
    void writeNotBool(Register target, Register value);
    void writeEqualBool(Register target, Register rhs, Register lhs);
    void writeNotEqualBool(Register target, Register rhs, Register lhs);
    void writeLoadInt32(Register reg, i32 value);
    void writeAddInt32(Register target, Register rhs, Register lhs);
    void writeSubtractInt32(Register target, Register rhs, Register lhs);
    void writeMultiplyInt32(Register target, Register rhs, Register lhs);
    void writeDivideInt32(Register target, Register rhs, Register lhs);
    void writeNegateInt32(Register target, Register value);
    void writeEqualInt32(Register target, Register rhs, Register lhs);
    void writeNotEqualInt32(Register target, Register rhs, Register lhs);
    void writeGreaterInt32(Register target, Register rhs, Register lhs);
    void writeGreaterOrEqualInt32(Register target, Register rhs, Register lhs);
    void writeLessInt32(Register target, Register rhs, Register lhs);
    void writeLessOrEqualInt32(Register target, Register rhs, Register lhs);
    void writeJump(u16 target);
    void writeHalt();

    u8 readUInt8();
    u16 readUInt16();
    i32 readInt32();

    void setInstructionPointer(u16 value);

private:
    i32 m_ip = 0;
    std::vector<u8> m_byteCode;

    inline void writeUInt8(u8 value);
    inline void writeUInt16(u16 value);
    inline void writeInt32(i32 value);
};
