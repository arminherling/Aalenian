#include <QTest>
#include <QDirIterator>

#include <Compiler/DiagnosticsBag.h>
#include <Compiler/File.h>
#include <Syntax/Lexer.h>
#include <Syntax/Parser.h>
#include <Debug/ParseTreePrinter.h>

class ParserTests : public QObject
{
    Q_OBJECT

private slots:
    void FileTests_data()
    {
        QTest::addColumn<QString>("inputFilePath");
        QTest::addColumn<QString>("outputFilePath");
        QTest::addColumn<QString>("errorFilePath");

        auto appDir = QDir(QCoreApplication::applicationDirPath());
        auto testDataDir = QDir(appDir.filePath(QString("../../Tests/Data")));
        auto absolutePath = testDataDir.absolutePath();

        QDirIterator it(absolutePath, QStringList() << QString("*.in"), QDir::Filter::Files, QDirIterator::IteratorFlag::Subdirectories);
        while (it.hasNext())
        {
            auto file = QFileInfo(it.next());
            auto directory = QDir(file.absolutePath());
            auto fullFilePathWithoutExtension = directory.filePath(file.baseName());

            auto inPath = QDir::cleanPath(fullFilePathWithoutExtension + QString(".in"));
            auto outPath = QDir::cleanPath(fullFilePathWithoutExtension + QString(".out"));
            auto errorPath = QDir::cleanPath(fullFilePathWithoutExtension + QString(".error"));

            auto testName = directory.dirName() + '/' + file.completeBaseName();
            QTest::newRow(testName.toStdString().c_str()) << inPath << outPath << errorPath;
        }
    }

    void FileTests()
    {
        QFETCH(QString, inputFilePath);
        QFETCH(QString, outputFilePath);
        QFETCH(QString, errorFilePath);

        if (!QFile::exists(inputFilePath))
            QFAIL("In file missing");
        if (!QFile::exists(outputFilePath))
            QSKIP("Out file missing");

        auto input = File::ReadAllText(inputFilePath);
        auto source = std::make_shared<SourceText>(input);
        DiagnosticsBag diagnostics;

        auto tokens = Lex(source, diagnostics);

        auto startTime = std::chrono::high_resolution_clock::now();
        auto parseTree = Parse(tokens, diagnostics);
        auto endTime = std::chrono::high_resolution_clock::now();

        auto elapsed_time_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        qDebug() << "Time: " << elapsed_time_ms << "ns";

        ParseTreePrinter printer{ parseTree };
        auto output = printer.PrettyPrint();

        auto expectedOutput = File::ReadAllText(outputFilePath);

        QCOMPARE(output, expectedOutput);
        if (!QFile::exists(errorFilePath))
        {
            QVERIFY(diagnostics.Diagnostics().empty());
        }
        else
        {
            QFAIL("TODO compare errors with error file once we got some");
        }
    }
};

QTEST_MAIN(ParserTests)
#include "ParserTests.moc"
