#pragma once

#include <API.h>
#include <TypeDefs.h>
#include <VirtualMachine/ByteCode.h>
#include <VirtualMachine/Register.h>
#include <VirtualMachine/Label.h>

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
    Label writeLabel();
    u16 writeJump();
    void writeJump(Label label);
    u16 writeJumpIfFalse(Register value);
    void writeJumpIfFalse(Register value, Label label);
    void patchJumpTarget(u16 jumpIndex, Label label);
    void writePrintBool(Register reg);
    void writePrintInt32(Register reg);
    void writePrintNewLine();
    void writeHalt();

private:
    ByteCode& m_byteCode;
};

