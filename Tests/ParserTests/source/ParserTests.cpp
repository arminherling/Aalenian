#include <QTest>

class ParserTests : public QObject
{
    Q_OBJECT

private slots:
    void Fail()
    {
        QFAIL("");
    }
};

QTEST_MAIN(ParserTests)
#include "ParserTests.moc"
