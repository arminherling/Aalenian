#include "ByteCodeAssembler.h"

#include <VirtualMachine/Op.h>

ByteCodeAssembler::ByteCodeAssembler(ByteCode& byteCode)
    : m_byteCode{ byteCode }
{
}

void ByteCodeAssembler::emitLoadBool(Register reg, bool value)
{
    m_byteCode.writeUInt8(Op::LoadBool);
    m_byteCode.writeUInt16(reg.index);
    m_byteCode.writeUInt8(value);
}

void ByteCodeAssembler::emitNotBool(Register target, Register value)
{
    m_byteCode.writeUInt8(Op::NotBool);
    m_byteCode.writeUInt16(target.index);
    m_byteCode.writeUInt16(value.index);
}

void ByteCodeAssembler::emitEqualBool(Register target, Register rhs, Register lhs)
{
    m_byteCode.writeUInt8(Op::EqualBool);
    m_byteCode.writeUInt16(target.index);
    m_byteCode.writeUInt16(rhs.index);
    m_byteCode.writeUInt16(lhs.index);
}

void ByteCodeAssembler::emitNotEqualBool(Register target, Register rhs, Register lhs)
{
    m_byteCode.writeUInt8(Op::NotEqualBool);
    m_byteCode.writeUInt16(target.index);
    m_byteCode.writeUInt16(rhs.index);
    m_byteCode.writeUInt16(lhs.index);
}

void ByteCodeAssembler::emitLoadInt32(Register reg, i32 value)
{
    m_byteCode.writeUInt8(Op::LoadInt32);
    m_byteCode.writeUInt16(reg.index);
    m_byteCode.writeInt32(value);
}

void ByteCodeAssembler::emitAddInt32(Register target, Register rhs, Register lhs)
{
    m_byteCode.writeUInt8(Op::AddInt32);
    m_byteCode.writeUInt16(target.index);
    m_byteCode.writeUInt16(rhs.index);
    m_byteCode.writeUInt16(lhs.index);
}

void ByteCodeAssembler::emitSubtractInt32(Register target, Register rhs, Register lhs)
{
    m_byteCode.writeUInt8(Op::SubtractInt32);
    m_byteCode.writeUInt16(target.index);
    m_byteCode.writeUInt16(rhs.index);
    m_byteCode.writeUInt16(lhs.index);
}

void ByteCodeAssembler::emitMultiplyInt32(Register target, Register rhs, Register lhs)
{
    m_byteCode.writeUInt8(Op::MultiplyInt32);
    m_byteCode.writeUInt16(target.index);
    m_byteCode.writeUInt16(rhs.index);
    m_byteCode.writeUInt16(lhs.index);
}

void ByteCodeAssembler::emitDivideInt32(Register target, Register rhs, Register lhs)
{
    m_byteCode.writeUInt8(Op::DivideInt32);
    m_byteCode.writeUInt16(target.index);
    m_byteCode.writeUInt16(rhs.index);
    m_byteCode.writeUInt16(lhs.index);
}

void ByteCodeAssembler::emitNegateInt32(Register target, Register value)
{
    m_byteCode.writeUInt8(Op::NegateInt32);
    m_byteCode.writeUInt16(target.index);
    m_byteCode.writeUInt16(value.index);
}

void ByteCodeAssembler::emitEqualInt32(Register target, Register rhs, Register lhs)
{
    m_byteCode.writeUInt8(Op::EqualInt32);
    m_byteCode.writeUInt16(target.index);
    m_byteCode.writeUInt16(rhs.index);
    m_byteCode.writeUInt16(lhs.index);
}

void ByteCodeAssembler::emitNotEqualInt32(Register target, Register rhs, Register lhs)
{
    m_byteCode.writeUInt8(Op::NotEqualInt32);
    m_byteCode.writeUInt16(target.index);
    m_byteCode.writeUInt16(rhs.index);
    m_byteCode.writeUInt16(lhs.index);
}

void ByteCodeAssembler::emitGreaterInt32(Register target, Register rhs, Register lhs)
{
    m_byteCode.writeUInt8(Op::GreaterInt32);
    m_byteCode.writeUInt16(target.index);
    m_byteCode.writeUInt16(rhs.index);
    m_byteCode.writeUInt16(lhs.index);
}

void ByteCodeAssembler::emitGreaterOrEqualInt32(Register target, Register rhs, Register lhs)
{
    m_byteCode.writeUInt8(Op::GreaterOrEqualInt32);
    m_byteCode.writeUInt16(target.index);
    m_byteCode.writeUInt16(rhs.index);
    m_byteCode.writeUInt16(lhs.index);
}

void ByteCodeAssembler::emitLessInt32(Register target, Register rhs, Register lhs)
{
    m_byteCode.writeUInt8(Op::LessInt32);
    m_byteCode.writeUInt16(target.index);
    m_byteCode.writeUInt16(rhs.index);
    m_byteCode.writeUInt16(lhs.index);
}

void ByteCodeAssembler::emitLessOrEqualInt32(Register target, Register rhs, Register lhs)
{
    m_byteCode.writeUInt8(Op::LessOrEqualInt32);
    m_byteCode.writeUInt16(target.index);
    m_byteCode.writeUInt16(rhs.index);
    m_byteCode.writeUInt16(lhs.index);
}

void ByteCodeAssembler::emitMove(Register target, Register value)
{
    m_byteCode.writeUInt8(Op::Move);
    m_byteCode.writeUInt16(target.index);
    m_byteCode.writeUInt16(value.index);
}

Label ByteCodeAssembler::createLabel()
{
    return Label(m_byteCode.data.size());
}

FunctionDeclaration ByteCodeAssembler::declareFunction(const QString& name, u8 returnValues, u8 parameterValues)
{
    auto label = createLabel();
    auto declaration = FunctionDeclaration{ .name = name, .entryPoint = label, .returnValues = returnValues, .parameterValues = parameterValues };
    m_byteCode.setFunctionDeclaration(declaration);
    return declaration;
}

FunctionCallLocation ByteCodeAssembler::emitFunctionCall(const QString& name, Register resultTarget)
{
    m_byteCode.writeUInt8(Op::FunctionCall);
    auto entryPointIndex = (u16)m_byteCode.data.size();
    m_byteCode.writeUInt16(0xDEAD);
    m_byteCode.writeUInt16(resultTarget.index);
    return FunctionCallLocation{ name, entryPointIndex };
}

u16 ByteCodeAssembler::emitJump()
{
    m_byteCode.writeUInt8(Op::Jump);
    auto targetIndex = (u16)m_byteCode.data.size();
    m_byteCode.writeUInt16(0xDEAD);
    return targetIndex;
}

void ByteCodeAssembler::emitJump(Label label)
{
    m_byteCode.writeUInt8(Op::Jump);
    m_byteCode.writeUInt16(label.index);
}

u16 ByteCodeAssembler::emitJumpIfFalse(Register value)
{
    m_byteCode.writeUInt8(Op::JumpIfFalse);
    m_byteCode.writeUInt16(value.index);
    auto targetIndex = m_byteCode.data.size();
    m_byteCode.writeUInt16(0xDEAD);
    return targetIndex;
}

void ByteCodeAssembler::emitJumpIfFalse(Register value, Label label)
{
    m_byteCode.writeUInt8(Op::JumpIfFalse);
    m_byteCode.writeUInt16(value.index);
    m_byteCode.writeUInt16(label.index);
}

void ByteCodeAssembler::patchJumpTarget(u16 jumpIndex, Label label)
{
    m_byteCode.writeUInt16(label.index, jumpIndex);
}

void ByteCodeAssembler::emitPrintBool(Register reg)
{
    m_byteCode.writeUInt8(Op::PrintBool);
    m_byteCode.writeUInt16(reg.index);
}

void ByteCodeAssembler::emitPrintInt32(Register reg)
{
    m_byteCode.writeUInt8(Op::PrintInt32);
    m_byteCode.writeUInt16(reg.index);
}

void ByteCodeAssembler::emitPrintNewLine()
{
    m_byteCode.writeUInt8(Op::PrintNewLine);
}

void ByteCodeAssembler::emitHalt()
{
    m_byteCode.writeUInt8(Op::Halt);
}
