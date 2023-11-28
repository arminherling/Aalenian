#pragma once

#include <API.h>
#include <TypeDefs.h>
#include <VirtualMachine/ByteCode.h>
#include <VirtualMachine/Register.h>

class COMPILER_API ByteCodeAssembler
{
public:
    ByteCodeAssembler(ByteCode& byteCode);

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
    void writeJumpIfFalse(u16 target, Register value);
    void writePrintBool(Register reg);
    void writePrintInt32(Register reg);
    void writePrintNewLine();
    void writeHalt();

private:
    ByteCode& m_byteCode;
};

