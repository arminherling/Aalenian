#include <QTest>

#include <VirtualMachine/ByteCode.h>
#include <VirtualMachine/ByteCodeAssembler.h>
#include <VirtualMachine/Register.h>
#include <VirtualMachine/VM.h>

#include <Debug/ByteCodeDisassembler.h>

class VirtualMachineTests : public QObject
{
    Q_OBJECT

private slots:
    void LoadBool_data()
    {
        QTest::addColumn<bool>("value");

        QTest::newRow("true") << true;
        QTest::newRow("false") << false;
    }

    void LoadBool()
    {
        QFETCH(bool, value);

        ByteCode code;
        ByteCodeAssembler assembler{ code };
        assembler.emitLoadBool(1, value);
        assembler.emitHalt();
        VM vm;

        auto startTime = std::chrono::high_resolution_clock::now();
        vm.run(code);
        auto endTime = std::chrono::high_resolution_clock::now();

        auto elapsed_time_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        qDebug() << "Time: " << elapsed_time_ms << "ns";

        auto loadedValue = vm.getValue(1);
        QCOMPARE(loadedValue.type, Value::Type::Bool);
        QCOMPARE(loadedValue.as.boolean, value);
    }

    void NotBool_data()
    {
        QTest::addColumn<bool>("value");
        QTest::addColumn<bool>("expectedResult");

        QTest::newRow("!true = false") << true << false;
        QTest::newRow("!false = true") << false << true;
    }

    void NotBool()
    {
        QFETCH(bool, value);
        QFETCH(bool, expectedResult);

        ByteCode code;
        ByteCodeAssembler assembler{ code };
        assembler.emitLoadBool(1, value);
        assembler.emitNotBool(0, 1);
        assembler.emitHalt();
        VM vm;

        auto startTime = std::chrono::high_resolution_clock::now();
        vm.run(code);
        auto endTime = std::chrono::high_resolution_clock::now();

        auto elapsed_time_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        qDebug() << "Time: " << elapsed_time_ms << "ns";

        auto loadedValue = vm.getValue(0);
        QCOMPARE(loadedValue.type, Value::Type::Bool);
        QCOMPARE(loadedValue.as.boolean, expectedResult);
    }

    void EqualBool_data()
    {
        QTest::addColumn<bool>("lhs");
        QTest::addColumn<bool>("rhs");
        QTest::addColumn<bool>("expectedResult");

        QTest::newRow("true == false = false") << true << false << false;
        QTest::newRow("true == true = true") << true << true << true;
        QTest::newRow("false == false = true") << false << false << true;
    }

    void EqualBool()
    {
        QFETCH(bool, lhs);
        QFETCH(bool, rhs);
        QFETCH(bool, expectedResult);

        ByteCode code;
        ByteCodeAssembler assembler{ code };
        assembler.emitLoadBool(1, lhs);
        assembler.emitLoadBool(2, rhs);
        assembler.emitEqualBool(0, 1, 2);
        assembler.emitHalt();
        VM vm;

        auto startTime = std::chrono::high_resolution_clock::now();
        vm.run(code);
        auto endTime = std::chrono::high_resolution_clock::now();

        auto elapsed_time_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        qDebug() << "Time: " << elapsed_time_ms << "ns";

        auto loadedValue = vm.getValue(0);
        QCOMPARE(loadedValue.type, Value::Type::Bool);
        QCOMPARE(loadedValue.as.boolean, expectedResult);
    }

    void NotEqualBool_data()
    {
        QTest::addColumn<bool>("lhs");
        QTest::addColumn<bool>("rhs");
        QTest::addColumn<bool>("expectedResult");

        QTest::newRow("true != false = true") << true << false << true;
        QTest::newRow("true != true = false") << true << true << false;
        QTest::newRow("false != false = false") << false << false << false;
    }

    void NotEqualBool()
    {
        QFETCH(bool, lhs);
        QFETCH(bool, rhs);
        QFETCH(bool, expectedResult);

        ByteCode code;
        ByteCodeAssembler assembler{ code };
        assembler.emitLoadBool(1, lhs);
        assembler.emitLoadBool(2, rhs);
        assembler.emitNotEqualBool(0, 1, 2);
        assembler.emitHalt();
        VM vm;

        auto startTime = std::chrono::high_resolution_clock::now();
        vm.run(code);
        auto endTime = std::chrono::high_resolution_clock::now();

        auto elapsed_time_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        qDebug() << "Time: " << elapsed_time_ms << "ns";

        auto loadedValue = vm.getValue(0);
        QCOMPARE(loadedValue.type, Value::Type::Bool);
        QCOMPARE(loadedValue.as.boolean, expectedResult);
    }

    void LoadInt32_data()
    {
        QTest::addColumn<i32>("value");

        QTest::newRow("123") << 123;
        QTest::newRow("-100000") << -100000;
    }

    void LoadInt32()
    {
        QFETCH(i32, value);

        ByteCode code;
        ByteCodeAssembler assembler{ code };
        assembler.emitLoadInt32(1, value);
        assembler.emitHalt();
        VM vm;

        auto startTime = std::chrono::high_resolution_clock::now();
        vm.run(code);
        auto endTime = std::chrono::high_resolution_clock::now();

        auto elapsed_time_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        qDebug() << "Time: " << elapsed_time_ms << "ns";

        auto loadedValue = vm.getValue(1);
        QCOMPARE(loadedValue.type, Value::Type::Int32);
        QCOMPARE(loadedValue.as.int32, value);
    }
    
    void AddInt32_data()
    {
        QTest::addColumn<i32>("lhs");
        QTest::addColumn<i32>("rhs");
        QTest::addColumn<i32>("expectedResult");

        QTest::newRow("10 + 100 = 110") << 10 << 100 << 110;
        QTest::newRow("-500 + -100 = -600") << -500 << -100 << -600;
    }

    void AddInt32()
    {
        QFETCH(i32, lhs);
        QFETCH(i32, rhs);
        QFETCH(i32, expectedResult);

        ByteCode code;
        ByteCodeAssembler assembler{ code };
        assembler.emitLoadInt32(1, lhs);
        assembler.emitLoadInt32(2, rhs);
        assembler.emitAddInt32(0, 1, 2);
        assembler.emitHalt();
        VM vm;

        auto startTime = std::chrono::high_resolution_clock::now();
        vm.run(code);
        auto endTime = std::chrono::high_resolution_clock::now();

        auto elapsed_time_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        qDebug() << "Time: " << elapsed_time_ms << "ns";

        auto loadedValue = vm.getValue(0);
        QCOMPARE(loadedValue.type, Value::Type::Int32);
        QCOMPARE(loadedValue.as.int32, expectedResult);
    }

    void SubtractInt32_data()
    {
        QTest::addColumn<i32>("lhs");
        QTest::addColumn<i32>("rhs");
        QTest::addColumn<i32>("expectedResult");

        QTest::newRow("10 - 100 = -90") << 10 << 100 << -90;
        QTest::newRow("-500 - -100 = -400") << -500 << -100 << -400;
    }

    void SubtractInt32()
    {
        QFETCH(i32, lhs);
        QFETCH(i32, rhs);
        QFETCH(i32, expectedResult);

        ByteCode code;
        ByteCodeAssembler assembler{ code };
        assembler.emitLoadInt32(1, lhs);
        assembler.emitLoadInt32(2, rhs);
        assembler.emitSubtractInt32(0, 1, 2);
        assembler.emitHalt();
        VM vm;

        auto startTime = std::chrono::high_resolution_clock::now();
        vm.run(code);
        auto endTime = std::chrono::high_resolution_clock::now();

        auto elapsed_time_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        qDebug() << "Time: " << elapsed_time_ms << "ns";

        auto loadedValue = vm.getValue(0);
        QCOMPARE(loadedValue.type, Value::Type::Int32);
        QCOMPARE(loadedValue.as.int32, expectedResult);
    }

    void MultiplyInt32_data()
    {
        QTest::addColumn<i32>("lhs");
        QTest::addColumn<i32>("rhs");
        QTest::addColumn<i32>("expectedResult");

        QTest::newRow("10 * 100 = 1000") << 10 << 100 << 1000;
        QTest::newRow("5 * -100 = -500") << 5 << -100 << -500;
    }

    void MultiplyInt32()
    {
        QFETCH(i32, lhs);
        QFETCH(i32, rhs);
        QFETCH(i32, expectedResult);

        ByteCode code;
        ByteCodeAssembler assembler{ code };
        assembler.emitLoadInt32(1, lhs);
        assembler.emitLoadInt32(2, rhs);
        assembler.emitMultiplyInt32(0, 1, 2);
        assembler.emitHalt();
        VM vm;

        auto startTime = std::chrono::high_resolution_clock::now();
        vm.run(code);
        auto endTime = std::chrono::high_resolution_clock::now();

        auto elapsed_time_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        qDebug() << "Time: " << elapsed_time_ms << "ns";

        auto loadedValue = vm.getValue(0);
        QCOMPARE(loadedValue.type, Value::Type::Int32);
        QCOMPARE(loadedValue.as.int32, expectedResult);
    }

    void DivideInt32_data()
    {
        QTest::addColumn<i32>("lhs");
        QTest::addColumn<i32>("rhs");
        QTest::addColumn<i32>("expectedResult");

        QTest::newRow("100 / 10 = 10") << 100 << 10 << 10;
        QTest::newRow("-100 / 5 = -20") << -100 << 5 << -20;
    }

    void DivideInt32()
    {
        QFETCH(i32, lhs);
        QFETCH(i32, rhs);
        QFETCH(i32, expectedResult);

        ByteCode code;
        ByteCodeAssembler assembler{ code };
        assembler.emitLoadInt32(1, lhs);
        assembler.emitLoadInt32(2, rhs);
        assembler.emitDivideInt32(0, 1, 2);
        assembler.emitHalt();
        VM vm;

        auto startTime = std::chrono::high_resolution_clock::now();
        vm.run(code);
        auto endTime = std::chrono::high_resolution_clock::now();

        auto elapsed_time_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        qDebug() << "Time: " << elapsed_time_ms << "ns";

        auto loadedValue = vm.getValue(0);
        QCOMPARE(loadedValue.type, Value::Type::Int32);
        QCOMPARE(loadedValue.as.int32, expectedResult);
    }

    void NegateIn32_data()
    {
        QTest::addColumn<i32>("value");
        QTest::addColumn<i32>("expectedResult");

        QTest::newRow("-(10) = -10") << 10 << -10;
        QTest::newRow("-(-100) = 100") << -100 << 100;
        QTest::newRow("-(0) = 0") << 0 << 0;
    }

    void NegateIn32()
    {
        QFETCH(i32, value);
        QFETCH(i32, expectedResult);

        ByteCode code;
        ByteCodeAssembler assembler{ code };
        assembler.emitLoadInt32(1, value);
        assembler.emitNegateInt32(0, 1);
        assembler.emitHalt();
        VM vm;

        auto startTime = std::chrono::high_resolution_clock::now();
        vm.run(code);
        auto endTime = std::chrono::high_resolution_clock::now();

        auto elapsed_time_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        qDebug() << "Time: " << elapsed_time_ms << "ns";

        auto loadedValue = vm.getValue(0);
        QCOMPARE(loadedValue.type, Value::Type::Int32);
        QCOMPARE(loadedValue.as.int32, expectedResult);
    }

    void EqualInt32_data()
    {
        QTest::addColumn<i32>("lhs");
        QTest::addColumn<i32>("rhs");
        QTest::addColumn<bool>("expectedResult");

        QTest::newRow("100 == 10 = false") << 100 << 10 << false;
        QTest::newRow("5 == 5 = true") << 5 << 5 << true;
    }

    void EqualInt32()
    {
        QFETCH(i32, lhs);
        QFETCH(i32, rhs);
        QFETCH(bool, expectedResult);

        ByteCode code;
        ByteCodeAssembler assembler{ code };
        assembler.emitLoadInt32(1, lhs);
        assembler.emitLoadInt32(2, rhs);
        assembler.emitEqualInt32(0, 1, 2);
        assembler.emitHalt();
        VM vm;

        auto startTime = std::chrono::high_resolution_clock::now();
        vm.run(code);
        auto endTime = std::chrono::high_resolution_clock::now();

        auto elapsed_time_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        qDebug() << "Time: " << elapsed_time_ms << "ns";

        auto loadedValue = vm.getValue(0);
        QCOMPARE(loadedValue.type, Value::Type::Bool);
        QCOMPARE(loadedValue.as.boolean, expectedResult);
    }

    void NotEqualInt32_data()
    {
        QTest::addColumn<i32>("lhs");
        QTest::addColumn<i32>("rhs");
        QTest::addColumn<bool>("expectedResult");

        QTest::newRow("100 != 10 = true") << 100 << 10 << true;
        QTest::newRow("5 != 5 = false") << 5 << 5 << false;
    }

    void NotEqualInt32()
    {
        QFETCH(i32, lhs);
        QFETCH(i32, rhs);
        QFETCH(bool, expectedResult);

        ByteCode code;
        ByteCodeAssembler assembler{ code };
        assembler.emitLoadInt32(1, lhs);
        assembler.emitLoadInt32(2, rhs);
        assembler.emitNotEqualInt32(0, 1, 2);
        assembler.emitHalt();
        VM vm;

        auto startTime = std::chrono::high_resolution_clock::now();
        vm.run(code);
        auto endTime = std::chrono::high_resolution_clock::now();

        auto elapsed_time_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        qDebug() << "Time: " << elapsed_time_ms << "ns";

        auto loadedValue = vm.getValue(0);
        QCOMPARE(loadedValue.type, Value::Type::Bool);
        QCOMPARE(loadedValue.as.boolean, expectedResult);
    }

    void GreaterInt32_data()
    {
        QTest::addColumn<i32>("lhs");
        QTest::addColumn<i32>("rhs");
        QTest::addColumn<bool>("expectedResult");

        QTest::newRow("100 > 10 = true") << 100 << 10 << true;
        QTest::newRow("5 > 5 = false") << 5 << 5 << false;
        QTest::newRow("1 > 2 = false") << 1 << 2 << false;
    }

    void GreaterInt32()
    {
        QFETCH(i32, lhs);
        QFETCH(i32, rhs);
        QFETCH(bool, expectedResult);

        ByteCode code;
        ByteCodeAssembler assembler{ code };
        assembler.emitLoadInt32(1, lhs);
        assembler.emitLoadInt32(2, rhs);
        assembler.emitGreaterInt32(0, 1, 2);
        assembler.emitHalt();
        VM vm;

        auto startTime = std::chrono::high_resolution_clock::now();
        vm.run(code);
        auto endTime = std::chrono::high_resolution_clock::now();

        auto elapsed_time_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        qDebug() << "Time: " << elapsed_time_ms << "ns";

        auto loadedValue = vm.getValue(0);
        QCOMPARE(loadedValue.type, Value::Type::Bool);
        QCOMPARE(loadedValue.as.boolean, expectedResult);
    }

    void GreaterOrEqualInt32_data()
    {
        QTest::addColumn<i32>("lhs");
        QTest::addColumn<i32>("rhs");
        QTest::addColumn<bool>("expectedResult");

        QTest::newRow("100 >= 10 = true") << 100 << 10 << true;
        QTest::newRow("5 >= 5 = true") << 5 << 5 << true;
        QTest::newRow("1 >= 2 = false") << 1 << 2 << false;
    }

    void GreaterOrEqualInt32()
    {
        QFETCH(i32, lhs);
        QFETCH(i32, rhs);
        QFETCH(bool, expectedResult);

        ByteCode code;
        ByteCodeAssembler assembler{ code };
        assembler.emitLoadInt32(1, lhs);
        assembler.emitLoadInt32(2, rhs);
        assembler.emitGreaterOrEqualInt32(0, 1, 2);
        assembler.emitHalt();
        VM vm;

        auto startTime = std::chrono::high_resolution_clock::now();
        vm.run(code);
        auto endTime = std::chrono::high_resolution_clock::now();

        auto elapsed_time_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        qDebug() << "Time: " << elapsed_time_ms << "ns";

        auto loadedValue = vm.getValue(0);
        QCOMPARE(loadedValue.type, Value::Type::Bool);
        QCOMPARE(loadedValue.as.boolean, expectedResult);
    }

    void LessInt32_data()
    {
        QTest::addColumn<i32>("lhs");
        QTest::addColumn<i32>("rhs");
        QTest::addColumn<bool>("expectedResult");

        QTest::newRow("100 < 10 = false") << 100 << 10 << false;
        QTest::newRow("5 < 5 = false") << 5 << 5 << false;
        QTest::newRow("1 < 2 = true") << 1 << 2 << true;
    }

    void LessInt32()
    {
        QFETCH(i32, lhs);
        QFETCH(i32, rhs);
        QFETCH(bool, expectedResult);

        ByteCode code;
        ByteCodeAssembler assembler{ code };
        assembler.emitLoadInt32(1, lhs);
        assembler.emitLoadInt32(2, rhs);
        assembler.emitLessInt32(0, 1, 2);
        assembler.emitHalt();
        VM vm;

        auto startTime = std::chrono::high_resolution_clock::now();
        vm.run(code);
        auto endTime = std::chrono::high_resolution_clock::now();

        auto elapsed_time_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        qDebug() << "Time: " << elapsed_time_ms << "ns";

        auto loadedValue = vm.getValue(0);
        QCOMPARE(loadedValue.type, Value::Type::Bool);
        QCOMPARE(loadedValue.as.boolean, expectedResult);
    }

    void LessOrEqualInt32_data()
    {
        QTest::addColumn<i32>("lhs");
        QTest::addColumn<i32>("rhs");
        QTest::addColumn<bool>("expectedResult");

        QTest::newRow("100 <= 10 = false") << 100 << 10 << false;
        QTest::newRow("5 <= 5 = true") << 5 << 5 << true;
        QTest::newRow("1 <= 2 = true") << 1 << 2 << true;
    }

    void LessOrEqualInt32()
    {
        QFETCH(i32, lhs);
        QFETCH(i32, rhs);
        QFETCH(bool, expectedResult);

        ByteCode code;
        ByteCodeAssembler assembler{ code };
        assembler.emitLoadInt32(1, lhs);
        assembler.emitLoadInt32(2, rhs);
        assembler.emitLessOrEqualInt32(0, 1, 2);
        assembler.emitHalt();
        VM vm;

        auto startTime = std::chrono::high_resolution_clock::now();
        vm.run(code);
        auto endTime = std::chrono::high_resolution_clock::now();

        auto elapsed_time_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        qDebug() << "Time: " << elapsed_time_ms << "ns";

        auto loadedValue = vm.getValue(0);
        QCOMPARE(loadedValue.type, Value::Type::Bool);
        QCOMPARE(loadedValue.as.boolean, expectedResult);
    }

    void Jump()
    {
        ByteCode code;
        ByteCodeAssembler assembler{ code };
        assembler.emitLoadInt32(0, 10);
        auto jumpIndex = assembler.emitJump();
        assembler.emitLoadInt32(0, 20);
        auto endLabel = assembler.createLabel();
        assembler.patchJumpTarget(jumpIndex, endLabel);
        assembler.emitHalt();
        VM vm;

        auto startTime = std::chrono::high_resolution_clock::now();
        vm.run(code);
        auto endTime = std::chrono::high_resolution_clock::now();

        auto elapsed_time_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        qDebug() << "Time: " << elapsed_time_ms << "ns";

        auto loadedValue = vm.getValue(0);
        QCOMPARE(loadedValue.type, Value::Type::Int32);
        QCOMPARE(loadedValue.as.int32, 10);
    }

    void JumpIfFalse_data()
    {
        QTest::addColumn<bool>("condition");
        QTest::addColumn<i32>("expectedResult");

        QTest::newRow("false -> 10") << false << 10;
        QTest::newRow("true -> 20") << true << 20;
    }

    void JumpIfFalse()
    {
        QFETCH(bool, condition);
        QFETCH(i32, expectedResult);

        ByteCode code;
        ByteCodeAssembler assembler{ code };
        assembler.emitLoadBool(0, condition);
        assembler.emitLoadInt32(1, 10);
        auto jumpIndex = assembler.emitJumpIfFalse(0);
        assembler.emitLoadInt32(1, 20);
        auto endLabel = assembler.createLabel();
        assembler.patchJumpTarget(jumpIndex, endLabel);
        assembler.emitHalt();
        VM vm;

        auto startTime = std::chrono::high_resolution_clock::now();
        vm.run(code);
        auto endTime = std::chrono::high_resolution_clock::now();

        auto elapsed_time_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        qDebug() << "Time: " << elapsed_time_ms << "ns";

        auto loadedValue = vm.getValue(1);
        QCOMPARE(loadedValue.type, Value::Type::Int32);
        QCOMPARE(loadedValue.as.int32, expectedResult);
    }

    void Move_data()
    {
        QTest::addColumn<QVariant>("value");
        QTest::addColumn<Value::Type>("type");

        QTest::newRow("true") << QVariant::fromValue(true) << Value::Type::Bool;
        QTest::newRow("false") << QVariant::fromValue(false) << Value::Type::Bool;
        QTest::newRow("0") << QVariant::fromValue(0) << Value::Type::Int32;
        QTest::newRow("100") << QVariant::fromValue(100) << Value::Type::Int32;
        QTest::newRow("-99") << QVariant::fromValue(-99) << Value::Type::Int32;
    }

    void Move()
    {
        QFETCH(QVariant, value);
        QFETCH(Value::Type, type);

        ByteCode code;
        ByteCodeAssembler assembler{ code };
        switch (type)
        {
            case Value::Type::Bool:
                assembler.emitLoadBool(1, value.toBool());
                break;
            case Value::Type::Int32:
                assembler.emitLoadInt32(1, value.toInt());
                break;
            default:
                TODO();
        }
        assembler.emitMove(0, 1);
        assembler.emitHalt();
        VM vm;

        auto startTime = std::chrono::high_resolution_clock::now();
        vm.run(code);
        auto endTime = std::chrono::high_resolution_clock::now();

        auto elapsed_time_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        qDebug() << "Time: " << elapsed_time_ms << "ns";

        auto loadedValue = vm.getValue(0);
        QCOMPARE(loadedValue.type, type);
        switch (type)
        {
            case Value::Type::Bool:
                QCOMPARE(loadedValue.as.boolean, value);
                break;
            case Value::Type::Int32:
                QCOMPARE(loadedValue.as.int32, value);
                break;
            default:
                TODO();
        }
    }

    void PrintBool_data()
    {
        QTest::addColumn<bool>("value");

        QTest::newRow("true") << true;
        QTest::newRow("false") << false;
    }

    void PrintBool()
    {
        QFETCH(bool, value);

        ByteCode code;
        ByteCodeAssembler assembler{ code };
        assembler.emitLoadBool(0, value);
        assembler.emitPrintBool(0);
        assembler.emitPrintNewLine();
        assembler.emitHalt();
        VM vm;

        auto startTime = std::chrono::high_resolution_clock::now();
        vm.run(code);
        auto endTime = std::chrono::high_resolution_clock::now();

        auto elapsed_time_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        qDebug() << "Time: " << elapsed_time_ms << "ns";
    }

    void PrintInt32_data()
    {
        QTest::addColumn<i32>("value");

        QTest::newRow("0") << 0;
        QTest::newRow("12345") << 12345;
    }

    void PrintInt32()
    {
        QFETCH(i32, value);

        ByteCode code;
        ByteCodeAssembler assembler{ code };
        assembler.emitLoadInt32(0, value);
        assembler.emitPrintInt32(0);
        assembler.emitPrintNewLine();
        assembler.emitHalt();
        VM vm;

        auto startTime = std::chrono::high_resolution_clock::now();
        vm.run(code);
        auto endTime = std::chrono::high_resolution_clock::now();

        auto elapsed_time_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        qDebug() << "Time: " << elapsed_time_ms << "ns";
    }

    void PrintNewLine()
    {
        ByteCode code;
        ByteCodeAssembler assembler{ code };
        assembler.emitPrintNewLine();
        assembler.emitHalt();
        VM vm;

        auto startTime = std::chrono::high_resolution_clock::now();
        vm.run(code);
        auto endTime = std::chrono::high_resolution_clock::now();

        auto elapsed_time_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        qDebug() << "Time: " << elapsed_time_ms << "ns";
    }

    void LoweredWhileLoop()
    {
        // int i = 0;
        // while (i < 10)
        // {
        //     i = i + 1;
        // }

        ByteCode code;
        ByteCodeAssembler assembler{ code };
        assembler.emitLoadInt32(0, 0);                     //  int i = 0
        assembler.emitLoadInt32(1, 10);                    //  int literal 10
        auto beginLabel = assembler.createLabel();         // begin:
        assembler.emitLessInt32(2, 0, 1);                  //  i < 10
        auto endJumpIndex = assembler.emitJumpIfFalse(2);  //  goto end if false
        assembler.emitLoadInt32(3, 1);                     //  int literal 1
        assembler.emitAddInt32(0, 0, 3);                   //  i = i + 1
        assembler.emitJump(beginLabel);                    //  goto begin
        auto endLabel = assembler.createLabel();           // end:
        assembler.patchJumpTarget(endJumpIndex, endLabel);
        assembler.emitHalt();
        VM vm;

        auto startTime = std::chrono::high_resolution_clock::now();
        vm.run(code);
        auto endTime = std::chrono::high_resolution_clock::now();

        auto elapsed_time_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        qDebug() << "Time: " << elapsed_time_ms << "ns";

        auto loadedValue = vm.getValue(0);
        QCOMPARE(loadedValue.type, Value::Type::Int32);
        QCOMPARE(loadedValue.as.int32, 10);
    }

    void FunctionDeclaration()
    {
        auto functionName = QString("function");
        auto returnValues = 1;
        auto parameterValues = 2;

        ByteCode code;
        ByteCodeAssembler assembler{ code };
        assembler.declareFunction(functionName, returnValues, parameterValues);

        auto optDeclaration = code.getFunctionDeclaration(functionName);
        QVERIFY(optDeclaration.has_value());
        auto declaration = optDeclaration.value();
        QCOMPARE(declaration.name, functionName);
        QCOMPARE(declaration.returnValues, returnValues);
        QCOMPARE(declaration.parameterValues, parameterValues);
    }
};

QTEST_MAIN(VirtualMachineTests)
#include "VirtualMachineTests.moc"
