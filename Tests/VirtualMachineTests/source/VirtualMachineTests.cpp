#include <QTest>

#include <VirtualMachine/ByteCode.h>
#include <VirtualMachine/ByteCodeAssembler.h>
#include <VirtualMachine/Register.h>
#include <VirtualMachine/VM.h>

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
        assembler.writeLoadBool(1, value);
        assembler.writeHalt();
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
        assembler.writeLoadBool(1, value);
        assembler.writeNotBool(0, 1);
        assembler.writeHalt();
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
        assembler.writeLoadBool(1, lhs);
        assembler.writeLoadBool(2, rhs);
        assembler.writeEqualBool(0, 1, 2);
        assembler.writeHalt();
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
        assembler.writeLoadBool(1, lhs);
        assembler.writeLoadBool(2, rhs);
        assembler.writeNotEqualBool(0, 1, 2);
        assembler.writeHalt();
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
        assembler.writeLoadInt32(1, value);
        assembler.writeHalt();
        VM vm;

        auto startTime = std::chrono::high_resolution_clock::now();
        vm.run(code);
        auto endTime = std::chrono::high_resolution_clock::now();

        auto elapsed_time_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        qDebug() << "Time: " << elapsed_time_ms << "ns";

        auto loadedValue = vm.getValue(1);
        QCOMPARE(loadedValue.type, Value::Type::I32);
        QCOMPARE(loadedValue.as.numI32, value);
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
        assembler.writeLoadInt32(1, lhs);
        assembler.writeLoadInt32(2, rhs);
        assembler.writeAddInt32(0, 1, 2);
        assembler.writeHalt();
        VM vm;

        auto startTime = std::chrono::high_resolution_clock::now();
        vm.run(code);
        auto endTime = std::chrono::high_resolution_clock::now();

        auto elapsed_time_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        qDebug() << "Time: " << elapsed_time_ms << "ns";

        auto loadedValue = vm.getValue(0);
        QCOMPARE(loadedValue.type, Value::Type::I32);
        QCOMPARE(loadedValue.as.numI32, expectedResult);
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
        assembler.writeLoadInt32(1, lhs);
        assembler.writeLoadInt32(2, rhs);
        assembler.writeSubtractInt32(0, 1, 2);
        assembler.writeHalt();
        VM vm;

        auto startTime = std::chrono::high_resolution_clock::now();
        vm.run(code);
        auto endTime = std::chrono::high_resolution_clock::now();

        auto elapsed_time_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        qDebug() << "Time: " << elapsed_time_ms << "ns";

        auto loadedValue = vm.getValue(0);
        QCOMPARE(loadedValue.type, Value::Type::I32);
        QCOMPARE(loadedValue.as.numI32, expectedResult);
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
        assembler.writeLoadInt32(1, lhs);
        assembler.writeLoadInt32(2, rhs);
        assembler.writeMultiplyInt32(0, 1, 2);
        assembler.writeHalt();
        VM vm;

        auto startTime = std::chrono::high_resolution_clock::now();
        vm.run(code);
        auto endTime = std::chrono::high_resolution_clock::now();

        auto elapsed_time_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        qDebug() << "Time: " << elapsed_time_ms << "ns";

        auto loadedValue = vm.getValue(0);
        QCOMPARE(loadedValue.type, Value::Type::I32);
        QCOMPARE(loadedValue.as.numI32, expectedResult);
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
        assembler.writeLoadInt32(1, lhs);
        assembler.writeLoadInt32(2, rhs);
        assembler.writeDivideInt32(0, 1, 2);
        assembler.writeHalt();
        VM vm;

        auto startTime = std::chrono::high_resolution_clock::now();
        vm.run(code);
        auto endTime = std::chrono::high_resolution_clock::now();

        auto elapsed_time_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        qDebug() << "Time: " << elapsed_time_ms << "ns";

        auto loadedValue = vm.getValue(0);
        QCOMPARE(loadedValue.type, Value::Type::I32);
        QCOMPARE(loadedValue.as.numI32, expectedResult);
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
        assembler.writeLoadInt32(1, value);
        assembler.writeNegateInt32(0, 1);
        assembler.writeHalt();
        VM vm;

        auto startTime = std::chrono::high_resolution_clock::now();
        vm.run(code);
        auto endTime = std::chrono::high_resolution_clock::now();

        auto elapsed_time_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        qDebug() << "Time: " << elapsed_time_ms << "ns";

        auto loadedValue = vm.getValue(0);
        QCOMPARE(loadedValue.type, Value::Type::I32);
        QCOMPARE(loadedValue.as.numI32, expectedResult);
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
        assembler.writeLoadInt32(1, lhs);
        assembler.writeLoadInt32(2, rhs);
        assembler.writeEqualInt32(0, 1, 2);
        assembler.writeHalt();
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
        assembler.writeLoadInt32(1, lhs);
        assembler.writeLoadInt32(2, rhs);
        assembler.writeNotEqualInt32(0, 1, 2);
        assembler.writeHalt();
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
        assembler.writeLoadInt32(1, lhs);
        assembler.writeLoadInt32(2, rhs);
        assembler.writeGreaterInt32(0, 1, 2);
        assembler.writeHalt();
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
        assembler.writeLoadInt32(1, lhs);
        assembler.writeLoadInt32(2, rhs);
        assembler.writeGreaterOrEqualInt32(0, 1, 2);
        assembler.writeHalt();
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
        assembler.writeLoadInt32(1, lhs);
        assembler.writeLoadInt32(2, rhs);
        assembler.writeLessInt32(0, 1, 2);
        assembler.writeHalt();
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
        assembler.writeLoadInt32(1, lhs);
        assembler.writeLoadInt32(2, rhs);
        assembler.writeLessOrEqualInt32(0, 1, 2);
        assembler.writeHalt();
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
        assembler.writeLoadInt32(0, 10);
        assembler.writeJump(17); //Skip 7 byte for LoadInt32, 3 for Jump, 7 for LoadInt32 = Target is 17
        assembler.writeLoadInt32(0, 20);
        assembler.writeHalt();
        VM vm;

        auto startTime = std::chrono::high_resolution_clock::now();
        vm.run(code);
        auto endTime = std::chrono::high_resolution_clock::now();

        auto elapsed_time_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        qDebug() << "Time: " << elapsed_time_ms << "ns";

        auto loadedValue = vm.getValue(0);
        QCOMPARE(loadedValue.type, Value::Type::I32);
        QCOMPARE(loadedValue.as.numI32, 10);
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
        assembler.writeLoadBool(0, condition);
        assembler.writeLoadInt32(1, 10);
        assembler.writeJumpIfFalse(23, 0); //Skip 4 bytes for LoadBool, 7 byte for LoadInt32, 5 for Jump, 7 for LoadInt32 = Target is 23
        assembler.writeLoadInt32(1, 20);
        assembler.writeHalt();
        VM vm;

        auto startTime = std::chrono::high_resolution_clock::now();
        vm.run(code);
        auto endTime = std::chrono::high_resolution_clock::now();

        auto elapsed_time_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        qDebug() << "Time: " << elapsed_time_ms << "ns";

        auto loadedValue = vm.getValue(1);
        QCOMPARE(loadedValue.type, Value::Type::I32);
        QCOMPARE(loadedValue.as.numI32, expectedResult);
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
        assembler.writeLoadBool(0, value);
        assembler.writePrintBool(0);
        assembler.writePrintNewLine();
        assembler.writeHalt();
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
        assembler.writeLoadInt32(0, value);
        assembler.writePrintInt32(0);
        assembler.writePrintNewLine();
        assembler.writeHalt();
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
        assembler.writePrintNewLine();
        assembler.writeHalt();
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
        assembler.writeLoadInt32(0, 0);      // 7 byte, int i = 0
        assembler.writeLoadInt32(1, 10);     // 7 byte, int literal 10
        assembler.writeLessInt32(2, 0, 1);   // 7 byte, i < 10
        assembler.writeJumpIfFalse(43, 2);   // 5 byte, goto end
        assembler.writeLoadInt32(3, 1);      // 7 byte, int literal 1
        assembler.writeAddInt32(0, 0, 3);    // 7 byte, i = i + 1
        assembler.writeJump(14);             // 3 byte, goto start of the loop before the check
        assembler.writeHalt();
        VM vm;

        auto startTime = std::chrono::high_resolution_clock::now();
        vm.run(code);
        auto endTime = std::chrono::high_resolution_clock::now();

        auto elapsed_time_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        qDebug() << "Time: " << elapsed_time_ms << "ns";

        auto loadedValue = vm.getValue(0);
        QCOMPARE(loadedValue.type, Value::Type::I32);
        QCOMPARE(loadedValue.as.numI32, 10);
    }
};

QTEST_MAIN(VirtualMachineTests)
#include "VirtualMachineTests.moc"
