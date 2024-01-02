#include "ParserTests.h"
#include <AalTest.h>
#include <Compiler/DiagnosticsBag.h>
#include <Compiler/File.h>
#include <Debug/ParseTreePrinter.h>
#include <iostream>
#include <QCoreApplication>
#include <QDirIterator>
#include <Syntax/Lexer.h>
#include <Syntax/Parser.h>

namespace
{
    void FileTests(const QString& fileName, const QString& inputFilePath, const QString& outputFilePath, const QString& errorFilePath)
    {
        if (!QFile::exists(inputFilePath))
            AalTest::Fail();// ("In file missing");
        if (!QFile::exists(outputFilePath))
            AalTest::Skip();// ("Out file missing");

        auto input = File::ReadAllText(inputFilePath);
        auto source = std::make_shared<SourceText>(input);
        DiagnosticsBag diagnostics;

        auto tokens = Lex(source, diagnostics);

        auto startTime = std::chrono::high_resolution_clock::now();
        auto parseTree = Parse(tokens, diagnostics);
        auto endTime = std::chrono::high_resolution_clock::now();

        std::cout << "   Parse(): " << Stringify(endTime - startTime).toStdString() << std::endl;

        ParseTreePrinter printer{ parseTree };
        auto output = printer.PrettyPrint();
        auto expectedOutput = File::ReadAllText(outputFilePath);

        AalTest::AreEqual(output, expectedOutput);
        if (!QFile::exists(errorFilePath))
        {
            AalTest::IsTrue(diagnostics.Diagnostics().empty());
        }
        else
        {
            AalTest::Fail();// ("TODO compare errors with error file once we got some");
        }
    }

    QList<std::tuple<QString, QString, QString, QString>> FileTests_Data()
    {
        auto appDir = QDir(QCoreApplication::applicationDirPath());
        auto testDataDir = QDir(appDir.filePath(QString("../../Tests/Data")));
        auto absolutePath = testDataDir.absolutePath();

        QList<std::tuple<QString, QString, QString, QString>> data{};

        QDirIterator it(absolutePath, QStringList() << QString("*.in"), QDir::Filter::Files, QDirIterator::IteratorFlag::Subdirectories);
        while (it.hasNext())
        {
            auto file = QFileInfo(it.next());
            auto directory = QDir(file.absolutePath());
            auto fullFilePathWithoutExtension = directory.filePath(file.baseName());

            auto inPath = QDir::cleanPath(fullFilePathWithoutExtension + QString(".in"));
            auto outPath = QDir::cleanPath(fullFilePathWithoutExtension + QString(".out_parse"));
            auto errorPath = QDir::cleanPath(fullFilePathWithoutExtension + QString(".error_parse"));

            auto testName = directory.dirName() + '/' + file.completeBaseName();
            data.append(std::make_tuple(testName, inPath, outPath, errorPath));
        }
        return data;
    }
}

TestSuite ParserTestsSuite()
{
    TestSuite suite{};

    suite.add(QString("FileTests"), FileTests, FileTests_Data);

    return suite;
}
