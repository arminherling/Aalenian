#include "VM.h"

#include <iostream>

VM::VM()
{
    m_registers.resize(2048);
}

void VM::setValue(Register reg, const Value& value)
{
    m_registers[reg.index] = value;
}

Value VM::getValue(Register reg)
{
    return m_registers[reg.index];
}

i32 VM::run(ByteCode& code)
{
    u16 ip = 0;

    while (true)
    {
        auto op = static_cast<Op>(code.readUInt8(ip));
        switch (op)
        {
            case Op::LoadBool:
            {
                auto reg = code.readUInt16(ip);
                auto value = (bool)code.readUInt8(ip);

                setValue(reg, value);

                break;
            }
            case Op::NotBool:
            {
                auto result = code.readUInt16(ip);
                auto value = code.readUInt16(ip);

                auto valueValue = getValue(value);

                auto resultValue = Value(!valueValue.as.boolean);
                setValue(result, resultValue);

                break;
            }
            case Op::EqualBool: 
            {
                auto result = code.readUInt16(ip);
                auto rhs = code.readUInt16(ip);
                auto lhs = code.readUInt16(ip);

                auto rhsValue = getValue(rhs);
                auto lhsValue = getValue(lhs);

                auto resultValue = Value(rhsValue.as.boolean == lhsValue.as.boolean);
                setValue(result, resultValue);

                break;
            }
            case Op::NotEqualBool:
            {
                auto result = code.readUInt16(ip);
                auto rhs = code.readUInt16(ip);
                auto lhs = code.readUInt16(ip);

                auto rhsValue = getValue(rhs);
                auto lhsValue = getValue(lhs);

                auto resultValue = Value(rhsValue.as.boolean != lhsValue.as.boolean);
                setValue(result, resultValue);

                break;
            }
            case Op::LoadInt32:
            {
                auto reg = code.readUInt16(ip);
                auto value = code.readInt32(ip);

                setValue(reg, value);

                break;
            }
            case Op::AddInt32:
            {
                auto result = code.readUInt16(ip);
                auto rhs = code.readUInt16(ip);
                auto lhs = code.readUInt16(ip);

                auto rhsValue = getValue(rhs);
                auto lhsValue = getValue(lhs);

                auto resultValue = Value(rhsValue.as.int32 + lhsValue.as.int32);
                setValue(result, resultValue);

                break;
            }
            case Op::SubtractInt32: 
            {
                auto result = code.readUInt16(ip);
                auto rhs = code.readUInt16(ip);
                auto lhs = code.readUInt16(ip);

                auto rhsValue = getValue(rhs);
                auto lhsValue = getValue(lhs);

                auto resultValue = Value(rhsValue.as.int32 - lhsValue.as.int32);
                setValue(result, resultValue);

                break;
            }
            case Op::MultiplyInt32:
            {
                auto result = code.readUInt16(ip);
                auto rhs = code.readUInt16(ip);
                auto lhs = code.readUInt16(ip);

                auto rhsValue = getValue(rhs);
                auto lhsValue = getValue(lhs);

                auto resultValue = Value(rhsValue.as.int32 * lhsValue.as.int32);
                setValue(result, resultValue);

                break;
            }
            case Op::DivideInt32:
            {
                auto result = code.readUInt16(ip);
                auto rhs = code.readUInt16(ip);
                auto lhs = code.readUInt16(ip);

                auto rhsValue = getValue(rhs);
                auto lhsValue = getValue(lhs);

                auto resultValue = Value(rhsValue.as.int32 / lhsValue.as.int32);
                setValue(result, resultValue);

                break;
            }
            case Op::NegateInt32:
            {
                auto result = code.readUInt16(ip);
                auto value = code.readUInt16(ip);

                auto valueValue = getValue(value);

                auto resultValue = Value(-valueValue.as.int32);
                setValue(result, resultValue);

                break;
            }
            case Op::EqualInt32:
            {
                auto result = code.readUInt16(ip);
                auto rhs = code.readUInt16(ip);
                auto lhs = code.readUInt16(ip);

                auto rhsValue = getValue(rhs);
                auto lhsValue = getValue(lhs);

                auto resultValue = Value(rhsValue.as.int32 == lhsValue.as.int32);
                setValue(result, resultValue);

                break;
            }
            case Op::NotEqualInt32:
            {
                auto result = code.readUInt16(ip);
                auto rhs = code.readUInt16(ip);
                auto lhs = code.readUInt16(ip);

                auto rhsValue = getValue(rhs);
                auto lhsValue = getValue(lhs);

                auto resultValue = Value(rhsValue.as.int32 != lhsValue.as.int32);
                setValue(result, resultValue);

                break;
            }
            case Op::GreaterInt32:
            {
                auto result = code.readUInt16(ip);
                auto rhs = code.readUInt16(ip);
                auto lhs = code.readUInt16(ip);

                auto rhsValue = getValue(rhs);
                auto lhsValue = getValue(lhs);

                auto resultValue = Value(rhsValue.as.int32 > lhsValue.as.int32);
                setValue(result, resultValue);

                break;
            }
            case Op::GreaterOrEqualInt32:
            {
                auto result = code.readUInt16(ip);
                auto rhs = code.readUInt16(ip);
                auto lhs = code.readUInt16(ip);

                auto rhsValue = getValue(rhs);
                auto lhsValue = getValue(lhs);

                auto resultValue = Value(rhsValue.as.int32 >= lhsValue.as.int32);
                setValue(result, resultValue);

                break;
            }
            case Op::LessInt32:
            {
                auto result = code.readUInt16(ip);
                auto rhs = code.readUInt16(ip);
                auto lhs = code.readUInt16(ip);

                auto rhsValue = getValue(rhs);
                auto lhsValue = getValue(lhs);

                auto resultValue = Value(rhsValue.as.int32 < lhsValue.as.int32);
                setValue(result, resultValue);

                break;
            }
            case Op::LessOrEqualInt32:
            {
                auto result = code.readUInt16(ip);
                auto rhs = code.readUInt16(ip);
                auto lhs = code.readUInt16(ip);

                auto rhsValue = getValue(rhs);
                auto lhsValue = getValue(lhs);

                auto resultValue = Value(rhsValue.as.int32 <= lhsValue.as.int32);
                setValue(result, resultValue);

                break;
            }
            case Op::Jump: 
            {
                auto target = code.readUInt16(ip);

                ip = target;

                break;
            }
            case Op::JumpIfFalse:
            {
                auto condition = code.readUInt16(ip);
                auto target = code.readUInt16(ip);

                auto conditionValue = getValue(condition);
                if(!conditionValue.as.boolean)
                    ip = target;

                break;
            }
            case Op::Move:
            {
                auto target = code.readUInt16(ip);
                auto source = code.readUInt16(ip);

                auto value = getValue(source);
                setValue(target, value);

                break;
            }
            case Op::PrintBool:
            {
                auto reg = code.readUInt16(ip);
                auto value = getValue(reg);

                std::cout << std::boolalpha << value.as.boolean;

                break;
            }
            case Op::PrintInt32:
            {
                auto reg = code.readUInt16(ip);
                auto value = getValue(reg);

                std::cout << value.as.int32;

                break;
            }
            case Op::PrintNewLine:
            {
                std::cout << '\n';

                break;
            }
            case Op::Halt:
            {
                return 0;
            }
            default:
                TODO("Operation was was not defined yet");
        }
    }

    return 0;
}
