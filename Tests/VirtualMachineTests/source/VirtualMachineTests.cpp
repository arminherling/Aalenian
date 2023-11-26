#include <QTest>

#include <VirtualMachine/ByteCode.h>
#include <VirtualMachine/Register.h>
#include <VirtualMachine/VM.h>

class VirtualMachineTests : public QObject
{
    Q_OBJECT

private slots:
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
        code.writeLoadInt32(1, value);
        code.writeHalt();
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
        code.writeLoadInt32(1, lhs);
        code.writeLoadInt32(2, rhs);
        code.writeAddInt32(0, 1, 2);
        code.writeHalt();
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
        code.writeLoadInt32(1, lhs);
        code.writeLoadInt32(2, rhs);
        code.writeSubtractInt32(0, 1, 2);
        code.writeHalt();
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

};

QTEST_MAIN(VirtualMachineTests)
#include "VirtualMachineTests.moc"
