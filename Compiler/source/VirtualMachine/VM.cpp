#include "VM.h"

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
    while (true)
    {
        auto op = static_cast<Op>(code.readUInt8());
        switch (op)
        {
            case Op::LoadBool:
            {
                auto reg = code.readUInt16();
                auto value = (bool)code.readUInt8();

                setValue(reg, value);

                break;
            }
            case Op::NotBool:
            {
                auto result = code.readUInt16();
                auto value = code.readUInt16();

                auto valueValue = getValue(value);

                auto resultValue = Value(!valueValue.as.boolean);
                setValue(result, resultValue);

                break;
            }
            case Op::EqualBool: 
            {
                auto result = code.readUInt16();
                auto rhs = code.readUInt16();
                auto lhs = code.readUInt16();

                auto rhsValue = getValue(rhs);
                auto lhsValue = getValue(lhs);

                auto resultValue = Value(rhsValue.as.boolean == lhsValue.as.boolean);
                setValue(result, resultValue);

                break;
            }
            case Op::NotEqualBool:
            {
                auto result = code.readUInt16();
                auto rhs = code.readUInt16();
                auto lhs = code.readUInt16();

                auto rhsValue = getValue(rhs);
                auto lhsValue = getValue(lhs);

                auto resultValue = Value(rhsValue.as.boolean != lhsValue.as.boolean);
                setValue(result, resultValue);

                break;
            }
            case Op::LoadInt32:
            {
                auto reg = code.readUInt16();
                auto value = code.readInt32();

                setValue(reg, value);

                break;
            }
            case Op::AddInt32:
            {
                auto result = code.readUInt16();
                auto rhs = code.readUInt16();
                auto lhs = code.readUInt16();

                auto rhsValue = getValue(rhs);
                auto lhsValue = getValue(lhs);

                auto resultValue = Value(rhsValue.as.numI32 + lhsValue.as.numI32);
                setValue(result, resultValue);

                break;
            }
            case Op::SubtractInt32: 
            {
                auto result = code.readUInt16();
                auto rhs = code.readUInt16();
                auto lhs = code.readUInt16();

                auto rhsValue = getValue(rhs);
                auto lhsValue = getValue(lhs);

                auto resultValue = Value(rhsValue.as.numI32 - lhsValue.as.numI32);
                setValue(result, resultValue);

                break;
            }
            case Op::MultiplyInt32:
            {
                auto result = code.readUInt16();
                auto rhs = code.readUInt16();
                auto lhs = code.readUInt16();

                auto rhsValue = getValue(rhs);
                auto lhsValue = getValue(lhs);

                auto resultValue = Value(rhsValue.as.numI32 * lhsValue.as.numI32);
                setValue(result, resultValue);

                break;
            }
            case Op::DivideInt32:
            {
                auto result = code.readUInt16();
                auto rhs = code.readUInt16();
                auto lhs = code.readUInt16();

                auto rhsValue = getValue(rhs);
                auto lhsValue = getValue(lhs);

                auto resultValue = Value(rhsValue.as.numI32 / lhsValue.as.numI32);
                setValue(result, resultValue);

                break;
            }
            case Op::NegateInt32:
            {
                auto result = code.readUInt16();
                auto value = code.readUInt16();

                auto valueValue = getValue(value);

                auto resultValue = Value(-valueValue.as.numI32);
                setValue(result, resultValue);

                break;
            }
            case Op::EqualInt32:
            {
                auto result = code.readUInt16();
                auto rhs = code.readUInt16();
                auto lhs = code.readUInt16();

                auto rhsValue = getValue(rhs);
                auto lhsValue = getValue(lhs);

                auto resultValue = Value(rhsValue.as.numI32 == lhsValue.as.numI32);
                setValue(result, resultValue);

                break;
            }
            case Op::NotEqualInt32:
            {
                auto result = code.readUInt16();
                auto rhs = code.readUInt16();
                auto lhs = code.readUInt16();

                auto rhsValue = getValue(rhs);
                auto lhsValue = getValue(lhs);

                auto resultValue = Value(rhsValue.as.numI32 != lhsValue.as.numI32);
                setValue(result, resultValue);

                break;
            }
            case Op::GreaterInt32:
            {
                auto result = code.readUInt16();
                auto rhs = code.readUInt16();
                auto lhs = code.readUInt16();

                auto rhsValue = getValue(rhs);
                auto lhsValue = getValue(lhs);

                auto resultValue = Value(rhsValue.as.numI32 > lhsValue.as.numI32);
                setValue(result, resultValue);

                break;
            }
            case Op::GreaterOrEqualInt32:
            {
                auto result = code.readUInt16();
                auto rhs = code.readUInt16();
                auto lhs = code.readUInt16();

                auto rhsValue = getValue(rhs);
                auto lhsValue = getValue(lhs);

                auto resultValue = Value(rhsValue.as.numI32 >= lhsValue.as.numI32);
                setValue(result, resultValue);

                break;
            }
            case Op::LessInt32:
            {
                auto result = code.readUInt16();
                auto rhs = code.readUInt16();
                auto lhs = code.readUInt16();

                auto rhsValue = getValue(rhs);
                auto lhsValue = getValue(lhs);

                auto resultValue = Value(rhsValue.as.numI32 < lhsValue.as.numI32);
                setValue(result, resultValue);

                break;
            }
            case Op::LessOrEqualInt32:
            {
                auto result = code.readUInt16();
                auto rhs = code.readUInt16();
                auto lhs = code.readUInt16();

                auto rhsValue = getValue(rhs);
                auto lhsValue = getValue(lhs);

                auto resultValue = Value(rhsValue.as.numI32 <= lhsValue.as.numI32);
                setValue(result, resultValue);

                break;
            }
            case Op::Halt:
            {
                return 0;
            }
            default:
            {
                assert(!"Operation was was not defined yet");
                break;
            }
        }
    }

    return 0;
}
