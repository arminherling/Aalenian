#include <QTest>

#include <Compiler/DiagnosticsBag.h>
#include <Compiler/Lexer.h>
#include <Compiler/Parser.h>

class ParserTests : public QObject
{
    Q_OBJECT

private slots:
    void GlobalStatements_data()
    {
        QTest::addColumn<QString>("input");
        QTest::addColumn<int>("expectedCount");
        QTest::addColumn<QList<NodeKind>>("expectedNodeKind");

        QTest::newRow("a = 1") 
            << QString("a = 1") 
            << 1 
            << (QList<NodeKind>() << NodeKind::AssignmentStatement);

        QTest::newRow("a = func()")
            << QString("a = func()")
            << 1
            << (QList<NodeKind>() << NodeKind::AssignmentStatement);

        QTest::newRow("_ = func()")
            << QString("_ = func()")
            << 1
            << (QList<NodeKind>() << NodeKind::AssignmentStatement);

        QTest::newRow("a = 1   b = a")
            << QString("a = 1   b = a")
            << 2
            << (QList<NodeKind>() << NodeKind::AssignmentStatement << NodeKind::AssignmentStatement);

        QTest::newRow("func()")
            << QString("func()")
            << 1
            << (QList<NodeKind>() << NodeKind::ExpressionStatement);

        QTest::newRow("define func() {  }")
            << QString("define func() {  }")
            << 1
            << (QList<NodeKind>() << NodeKind::FunctionDefinitionStatement);

        QTest::newRow("define func() { a = 0   return a }")
            << QString("define func() { a = 0   return a}")
            << 1
            << (QList<NodeKind>() << NodeKind::FunctionDefinitionStatement);
    }

    void GlobalStatements()
    {
        QFETCH(QString, input);
        QFETCH(int, expectedCount);
        QFETCH(QList<NodeKind>, expectedNodeKind);

        auto source = std::make_shared<SourceText>(input);
        DiagnosticsBag diagnostics;

        auto tokens = Lex(source, diagnostics);

        auto startTime = std::chrono::high_resolution_clock::now();
        auto parseTree = Parse(tokens, diagnostics);

        auto endTime = std::chrono::high_resolution_clock::now();
        double elapsed_time_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        qDebug() << "Time: " << elapsed_time_ms << "ns";

        auto statements = parseTree.GlobalStatements();

        QVERIFY(diagnostics.Diagnostics().empty());
        QCOMPARE(statements.count(), expectedCount);
        for (int i = 0; i < statements.size(); i++)
        {
            QCOMPARE(statements[i]->Kind(), expectedNodeKind[i]);
        }
    }
};

QTEST_MAIN(ParserTests)
#include "ParserTests.moc"
