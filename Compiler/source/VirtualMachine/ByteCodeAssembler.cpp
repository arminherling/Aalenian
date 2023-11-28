#include "ByteCodeAssembler.h"

ByteCodeAssembler::ByteCodeAssembler(ByteCode& byteCode)
    : m_byteCode{ byteCode }
{
}

void ByteCodeAssembler::writeLoadBool(Register reg, bool value)
{
    m_byteCode.writeUInt8(Op::LoadBool);
    m_byteCode.writeUInt16(reg.index);
    m_byteCode.writeUInt8(value);
}

void ByteCodeAssembler::writeNotBool(Register target, Register value)
{
    m_byteCode.writeUInt8(Op::NotBool);
    m_byteCode.writeUInt16(target.index);
    m_byteCode.writeUInt16(value.index);
}

void ByteCodeAssembler::writeEqualBool(Register target, Register rhs, Register lhs)
{
    m_byteCode.writeUInt8(Op::EqualBool);
    m_byteCode.writeUInt16(target.index);
    m_byteCode.writeUInt16(rhs.index);
    m_byteCode.writeUInt16(lhs.index);
}

void ByteCodeAssembler::writeNotEqualBool(Register target, Register rhs, Register lhs)
{
    m_byteCode.writeUInt8(Op::NotEqualBool);
    m_byteCode.writeUInt16(target.index);
    m_byteCode.writeUInt16(rhs.index);
    m_byteCode.writeUInt16(lhs.index);
}

void ByteCodeAssembler::writeLoadInt32(Register reg, i32 value)
{
    m_byteCode.writeUInt8(Op::LoadInt32);
    m_byteCode.writeUInt16(reg.index);
    m_byteCode.writeInt32(value);
}

void ByteCodeAssembler::writeAddInt32(Register target, Register rhs, Register lhs)
{
    m_byteCode.writeUInt8(Op::AddInt32);
    m_byteCode.writeUInt16(target.index);
    m_byteCode.writeUInt16(rhs.index);
    m_byteCode.writeUInt16(lhs.index);
}

void ByteCodeAssembler::writeSubtractInt32(Register target, Register rhs, Register lhs)
{
    m_byteCode.writeUInt8(Op::SubtractInt32);
    m_byteCode.writeUInt16(target.index);
    m_byteCode.writeUInt16(rhs.index);
    m_byteCode.writeUInt16(lhs.index);
}

void ByteCodeAssembler::writeMultiplyInt32(Register target, Register rhs, Register lhs)
{
    m_byteCode.writeUInt8(Op::MultiplyInt32);
    m_byteCode.writeUInt16(target.index);
    m_byteCode.writeUInt16(rhs.index);
    m_byteCode.writeUInt16(lhs.index);
}

void ByteCodeAssembler::writeDivideInt32(Register target, Register rhs, Register lhs)
{
    m_byteCode.writeUInt8(Op::DivideInt32);
    m_byteCode.writeUInt16(target.index);
    m_byteCode.writeUInt16(rhs.index);
    m_byteCode.writeUInt16(lhs.index);
}

void ByteCodeAssembler::writeNegateInt32(Register target, Register value)
{
    m_byteCode.writeUInt8(Op::NegateInt32);
    m_byteCode.writeUInt16(target.index);
    m_byteCode.writeUInt16(value.index);
}

void ByteCodeAssembler::writeEqualInt32(Register target, Register rhs, Register lhs)
{
    m_byteCode.writeUInt8(Op::EqualInt32);
    m_byteCode.writeUInt16(target.index);
    m_byteCode.writeUInt16(rhs.index);
    m_byteCode.writeUInt16(lhs.index);
}

void ByteCodeAssembler::writeNotEqualInt32(Register target, Register rhs, Register lhs)
{
    m_byteCode.writeUInt8(Op::NotEqualInt32);
    m_byteCode.writeUInt16(target.index);
    m_byteCode.writeUInt16(rhs.index);
    m_byteCode.writeUInt16(lhs.index);
}

void ByteCodeAssembler::writeGreaterInt32(Register target, Register rhs, Register lhs)
{
    m_byteCode.writeUInt8(Op::GreaterInt32);
    m_byteCode.writeUInt16(target.index);
    m_byteCode.writeUInt16(rhs.index);
    m_byteCode.writeUInt16(lhs.index);
}

void ByteCodeAssembler::writeGreaterOrEqualInt32(Register target, Register rhs, Register lhs)
{
    m_byteCode.writeUInt8(Op::GreaterOrEqualInt32);
    m_byteCode.writeUInt16(target.index);
    m_byteCode.writeUInt16(rhs.index);
    m_byteCode.writeUInt16(lhs.index);
}

void ByteCodeAssembler::writeLessInt32(Register target, Register rhs, Register lhs)
{
    m_byteCode.writeUInt8(Op::LessInt32);
    m_byteCode.writeUInt16(target.index);
    m_byteCode.writeUInt16(rhs.index);
    m_byteCode.writeUInt16(lhs.index);
}

void ByteCodeAssembler::writeLessOrEqualInt32(Register target, Register rhs, Register lhs)
{
    m_byteCode.writeUInt8(Op::LessOrEqualInt32);
    m_byteCode.writeUInt16(target.index);
    m_byteCode.writeUInt16(rhs.index);
    m_byteCode.writeUInt16(lhs.index);
}

void ByteCodeAssembler::writeJump(u16 target)
{
    m_byteCode.writeUInt8(Op::Jump);
    m_byteCode.writeUInt16(target);
}

void ByteCodeAssembler::writeJumpIfFalse(u16 target, Register value)
{
    m_byteCode.writeUInt8(Op::JumpIfFalse);
    m_byteCode.writeUInt16(target);
    m_byteCode.writeUInt16(value.index);
}

void ByteCodeAssembler::writePrintBool(Register reg)
{
    m_byteCode.writeUInt8(Op::PrintBool);
    m_byteCode.writeUInt16(reg.index);
}

void ByteCodeAssembler::writePrintInt32(Register reg)
{
    m_byteCode.writeUInt8(Op::PrintInt32);
    m_byteCode.writeUInt16(reg.index);
}

void ByteCodeAssembler::writePrintNewLine()
{
    m_byteCode.writeUInt8(Op::PrintNewLine);
}

void ByteCodeAssembler::writeHalt()
{
    m_byteCode.writeUInt8(Op::Halt);
}
