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
            case Op::Halt:
            {
                return 0;
            }
            default:
                break;
        }
    }

    return 0;
}
