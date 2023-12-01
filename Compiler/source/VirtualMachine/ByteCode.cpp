#include "ByteCode.h"

inline u8 ByteCode::readUInt8(u16& ip) const
{
    return data[ip++];
}

inline u16 ByteCode::readUInt16(u16& ip) const
{
    return (u16)(data[ip++] | (data[ip++] << 8));
}

inline i32 ByteCode::readInt32(u16& ip) const
{
    return (i32)(data[ip++] | (data[ip++] << 8) | (data[ip++] << 16) | (data[ip++] << 24));
}

inline void ByteCode::writeUInt8(u8 value)
{
    data.emplace_back(value);
}

inline void ByteCode::writeUInt16(u16 value)
{
    data.emplace_back((value >> 0) & 0xFF);
    data.emplace_back((value >> 8) & 0xFF);
}

inline void ByteCode::writeUInt16(u16 value, u16 address)
{
    data[address] = ((value >> 0) & 0xFF);
    data[address+1] = ((value >> 8) & 0xFF);
}

inline void ByteCode::writeInt32(i32 value)
{
    data.emplace_back((value >> 0) & 0xFF);
    data.emplace_back((value >> 8) & 0xFF);
    data.emplace_back((value >> 16) & 0xFF);
    data.emplace_back((value >> 24) & 0xFF);
}

COMPILER_API QString StringifyOp(Op op)
{
    switch (op)
    {
        case Op::LoadBool:
            return QString("LoadBool");
        case Op::NotBool:
            return QString("NotBool");
        case Op::EqualBool:
            return QString("EqualBool");
        case Op::NotEqualBool:
            return QString("NotEqualBool");
        case Op::LoadInt32:
            return QString("LoadInt32");
        case Op::AddInt32:
            return QString("AddInt32");
        case Op::SubtractInt32:
            return QString("SubtractInt32");
        case Op::MultiplyInt32:
            return QString("MultiplyInt32");
        case Op::DivideInt32:
            return QString("DivideInt32");
        case Op::NegateInt32:
            return QString("NegateInt32");
        case Op::EqualInt32:
            return QString("EqualInt32");
        case Op::NotEqualInt32:
            return QString("NotEqualInt32");
        case Op::GreaterInt32:
            return QString("GreaterInt32");
        case Op::GreaterOrEqualInt32:
            return QString("GreaterOrEqualInt32");
        case Op::LessInt32:
            return QString("LessInt32");
        case Op::LessOrEqualInt32:
            return QString("LessOrEqualInt32");
        case Op::Jump:
            return QString("Jump");
        case Op::JumpIfFalse:
            return QString("JumpIfFalse");
        case Op::PrintBool:
            return QString("PrintBool");
        case Op::PrintInt32:
            return QString("PrintInt32");
        case Op::PrintNewLine:
            return QString("PrintNewLine");
        case Op::Halt:
            return QString("Halt");
        default:
            TODO("String for Op code value was not defined yet");
    }
}
