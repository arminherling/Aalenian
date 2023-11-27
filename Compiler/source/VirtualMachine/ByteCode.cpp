#include "ByteCode.h"

void ByteCode::writeLoadBool(Register reg, bool value)
{
    writeUInt8(Op::LoadBool);
    writeUInt16(reg.index);
    writeUInt8(value);
}

void ByteCode::writeNotBool(Register target, Register value)
{
    writeUInt8(Op::NotBool);
    writeUInt16(target.index);
    writeUInt16(value.index);
}

void ByteCode::writeEqualBool(Register target, Register rhs, Register lhs)
{
    writeUInt8(Op::EqualBool);
    writeUInt16(target.index);
    writeUInt16(rhs.index);
    writeUInt16(lhs.index);
}

void ByteCode::writeNotEqualBool(Register target, Register rhs, Register lhs)
{
    writeUInt8(Op::NotEqualBool);
    writeUInt16(target.index);
    writeUInt16(rhs.index);
    writeUInt16(lhs.index);
}

void ByteCode::writeLoadInt32(Register reg, i32 value)
{
    writeUInt8(Op::LoadInt32);
    writeUInt16(reg.index);
    writeInt32(value);
}

void ByteCode::writeAddInt32(Register target, Register rhs, Register lhs)
{
    writeUInt8(Op::AddInt32);
    writeUInt16(target.index);
    writeUInt16(rhs.index);
    writeUInt16(lhs.index);
}

void ByteCode::writeSubtractInt32(Register target, Register rhs, Register lhs)
{
    writeUInt8(Op::SubtractInt32);
    writeUInt16(target.index);
    writeUInt16(rhs.index);
    writeUInt16(lhs.index);
}

void ByteCode::writeMultiplyInt32(Register target, Register rhs, Register lhs)
{
    writeUInt8(Op::MultiplyInt32);
    writeUInt16(target.index);
    writeUInt16(rhs.index);
    writeUInt16(lhs.index);
}

void ByteCode::writeDivideInt32(Register target, Register rhs, Register lhs)
{
    writeUInt8(Op::DivideInt32);
    writeUInt16(target.index);
    writeUInt16(rhs.index);
    writeUInt16(lhs.index);
}

void ByteCode::writeNegateInt32(Register target, Register value)
{
    writeUInt8(Op::NegateInt32);
    writeUInt16(target.index);
    writeUInt16(value.index);
}

void ByteCode::writeEqualInt32(Register target, Register rhs, Register lhs)
{
    writeUInt8(Op::EqualInt32);
    writeUInt16(target.index);
    writeUInt16(rhs.index);
    writeUInt16(lhs.index);
}

void ByteCode::writeNotEqualInt32(Register target, Register rhs, Register lhs)
{
    writeUInt8(Op::NotEqualInt32);
    writeUInt16(target.index);
    writeUInt16(rhs.index);
    writeUInt16(lhs.index);
}

void ByteCode::writeGreaterInt32(Register target, Register rhs, Register lhs)
{
    writeUInt8(Op::GreaterInt32);
    writeUInt16(target.index);
    writeUInt16(rhs.index);
    writeUInt16(lhs.index);
}

void ByteCode::writeGreaterOrEqualInt32(Register target, Register rhs, Register lhs)
{
    writeUInt8(Op::GreaterOrEqualInt32);
    writeUInt16(target.index);
    writeUInt16(rhs.index);
    writeUInt16(lhs.index);
}

void ByteCode::writeLessInt32(Register target, Register rhs, Register lhs)
{
    writeUInt8(Op::LessInt32);
    writeUInt16(target.index);
    writeUInt16(rhs.index);
    writeUInt16(lhs.index);
}

void ByteCode::writeLessOrEqualInt32(Register target, Register rhs, Register lhs)
{
    writeUInt8(Op::LessOrEqualInt32);
    writeUInt16(target.index);
    writeUInt16(rhs.index);
    writeUInt16(lhs.index);
}

void ByteCode::writeJump(u16 target)
{
    writeUInt8(Op::Jump);
    writeUInt16(target);
}

void ByteCode::writeHalt()
{
    writeUInt8(Op::Halt);
}

u8 ByteCode::readUInt8()
{
    return m_byteCode[m_ip++];
}

u16 ByteCode::readUInt16()
{
    return (u16)(m_byteCode[m_ip++] | (m_byteCode[m_ip++] << 8));
}

i32 ByteCode::readInt32()
{
    return (i32)(m_byteCode[m_ip++] | (m_byteCode[m_ip++] << 8) | (m_byteCode[m_ip++] << 16) | (m_byteCode[m_ip++] << 24));
}

void ByteCode::setInstructionPointer(u16 value)
{
    m_ip = value;
}

inline void ByteCode::writeUInt8(u8 value)
{
    m_byteCode.emplace_back(value);
}

inline void ByteCode::writeUInt16(u16 value)
{
    m_byteCode.emplace_back((value >> 0) & 0xFF);
    m_byteCode.emplace_back((value >> 8) & 0xFF);
}

inline void ByteCode::writeInt32(i32 value)
{
    m_byteCode.emplace_back((value >> 0) & 0xFF);
    m_byteCode.emplace_back((value >> 8) & 0xFF);
    m_byteCode.emplace_back((value >> 16) & 0xFF);
    m_byteCode.emplace_back((value >> 24) & 0xFF);
}
