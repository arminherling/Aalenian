#pragma once

#include <Defines.h>
#include <VirtualMachine/ByteCode.h>
#include <VirtualMachine/FunctionCallLocation.h>
#include <VirtualMachine/Register.h>
#include <VirtualMachine/Label.h>

class COMPILER_API ByteCodeAssembler
{
public:
    ByteCodeAssembler(ByteCode& byteCode);

    void emitLoadBool(Register reg, bool value);
    void emitNotBool(Register target, Register value);
    void emitEqualBool(Register target, Register rhs, Register lhs);
    void emitNotEqualBool(Register target, Register rhs, Register lhs);
    void emitLoadInt32(Register reg, i32 value);
    void emitAddInt32(Register target, Register rhs, Register lhs);
    void emitSubtractInt32(Register target, Register rhs, Register lhs);
    void emitMultiplyInt32(Register target, Register rhs, Register lhs);
    void emitDivideInt32(Register target, Register rhs, Register lhs);
    void emitNegateInt32(Register target, Register value);
    void emitEqualInt32(Register target, Register rhs, Register lhs);
    void emitNotEqualInt32(Register target, Register rhs, Register lhs);
    void emitGreaterInt32(Register target, Register rhs, Register lhs);
    void emitGreaterOrEqualInt32(Register target, Register rhs, Register lhs);
    void emitLessInt32(Register target, Register rhs, Register lhs);
    void emitLessOrEqualInt32(Register target, Register rhs, Register lhs);
    void emitMove(Register target, Register value);
    Label createLabel();
    FunctionDeclaration declareFunction(const QString& name, u8 returnValues, u8 parameterValues);
    FunctionCallLocation emitFunctionCall(const QString& name, Register resultTarget);
    u16 emitJump();
    void emitJump(Label label);
    u16 emitJumpIfFalse(Register value);
    void emitJumpIfFalse(Register value, Label label);
    void patchJumpTarget(u16 jumpIndex, Label label);
    void emitPrintBool(Register reg);
    void emitPrintInt32(Register reg);
    void emitPrintNewLine();
    void emitHalt();

private:
    ByteCode& m_byteCode;
};
