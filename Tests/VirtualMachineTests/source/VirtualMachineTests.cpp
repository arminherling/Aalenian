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

        auto startTime = std::chrono::high_resolution_clock::now();

        VM vm;
        vm.run(code);

        auto endTime = std::chrono::high_resolution_clock::now();
        auto elapsed_time_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        qDebug() << "Time: " << elapsed_time_ms << "ns";

        auto loadedValue = vm.getValue(1);
        QCOMPARE(loadedValue.type, Value::Type::I32);
        QCOMPARE(loadedValue.as.numI32, value);
    }
};

QTEST_MAIN(VirtualMachineTests)
#include "VirtualMachineTests.moc"