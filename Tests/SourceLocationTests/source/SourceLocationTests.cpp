#include <QTest>

#include <Syntax/Lexer.h>
#include <Syntax/Token.h>
#include <Syntax/TokenKind.h>
#include <Syntax/TokenBuffer.h>
#include <Text/SourceText.h>
#include <Text/SourceLocation.h>

#include <chrono>

class SourceLocationTests : public QObject
{
    Q_OBJECT

private slots:
    void SingleSourceLocation_data()
    {
        QTest::addColumn<SourceTextSharedPtr>("input");
        QTest::addColumn<SourceLocation>("expectedLocation");

        const static auto source1 = std::make_shared<SourceText>(QString("+"));
        QTest::newRow("+") << source1 
            << SourceLocation{.source = source1, .startIndex = 0, .endIndex = 1, .startColumn = 1, .endColumn = 2, .startLine = 1, .endLine = 1};

        const static auto source2 = std::make_shared<SourceText>(QString(" bar "));
        QTest::newRow(" bar ") << source2 
            << SourceLocation{.source = source2, .startIndex = 1, .endIndex = 4, .startColumn = 2, .endColumn = 5, .startLine = 1, .endLine = 1};

        const static auto source3 = std::make_shared<SourceText>(QString("\nreturn"));
        QTest::newRow("\\nreturn") << source3 
            << SourceLocation{.source = source3, .startIndex = 1, .endIndex = 7, .startColumn = 1, .endColumn = 7, .startLine = 2, .endLine = 2};

        const static auto source4 = std::make_shared<SourceText>(QString("\r\nreturn"));
        QTest::newRow("\\r\\nreturn") << source4 
            << SourceLocation{.source = source4, .startIndex = 2, .endIndex = 8, .startColumn = 1, .endColumn = 7, .startLine = 2, .endLine = 2};

        const static auto source5 = std::make_shared<SourceText>(QString("  1_234 "));
        QTest::newRow("  1_234 ") << source5
            << SourceLocation{.source = source5, .startIndex = 2, .endIndex = 7, .startColumn = 3, .endColumn = 8, .startLine = 1, .endLine = 1};

        const static auto source6 = std::make_shared<SourceText>(QString(" \"1234567890\""));
        QTest::newRow(" \"1234567890\"") << source6 
            << SourceLocation{.source = source6, .startIndex = 1, .endIndex = 13, .startColumn = 2, .endColumn = 14, .startLine = 1, .endLine = 1};

        const static auto source7 = std::make_shared<SourceText>(QString("$"));
        QTest::newRow("$") << source7
            << SourceLocation{.source = source7, .startIndex = 0, .endIndex = 1, .startColumn = 1, .endColumn = 2, .startLine = 1, .endLine = 1};
    }

    void SingleSourceLocation()
    {
        QFETCH(SourceTextSharedPtr, input);
        QFETCH(SourceLocation, expectedLocation);

        DiagnosticsBag diagnostics;

        auto startTime = std::chrono::high_resolution_clock::now();
        auto tokens = Lex(input, diagnostics);
        auto& token = tokens[0];

        auto endTime = std::chrono::high_resolution_clock::now();
        auto elapsed_time_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        qDebug() << "Time: " << elapsed_time_ms << "ns";

        auto& location = tokens.GetSourceLocation(token.locationIndex);
        QCOMPARE(location.startIndex, expectedLocation.startIndex);
        QCOMPARE(location.endIndex, expectedLocation.endIndex);
        QCOMPARE(location.startColumn, expectedLocation.startColumn);
        QCOMPARE(location.endColumn, expectedLocation.endColumn);
        QCOMPARE(location.startLine, expectedLocation.startLine);
        QCOMPARE(location.endLine, expectedLocation.endLine);
    }

    void MultipleSourceLocations()
    {
        auto input = std::make_shared<SourceText>(QString("define sum(a int, b int) \r\n {\r\n return a + b \r\n}\r\n"));
        auto expectedList = QList<SourceLocation>()
            << SourceLocation{.source = input, .startIndex = 0, .endIndex = 6, .startColumn = 1, .endColumn = 7, .startLine = 1, .endLine = 1 }  // define
            << SourceLocation{.source = input, .startIndex = 7, .endIndex = 10, .startColumn = 8, .endColumn = 11, .startLine = 1, .endLine = 1} // sum
            << SourceLocation{.source = input, .startIndex = 10, .endIndex = 11, .startColumn = 11, .endColumn = 12, .startLine = 1, .endLine = 1} // (
            << SourceLocation{.source = input, .startIndex = 11, .endIndex = 12, .startColumn = 12, .endColumn = 13, .startLine = 1, .endLine = 1} // a
            << SourceLocation{.source = input, .startIndex = 13, .endIndex = 16, .startColumn = 14, .endColumn = 17, .startLine = 1, .endLine = 1} // int
            << SourceLocation{.source = input, .startIndex = 16, .endIndex = 17, .startColumn = 17, .endColumn = 18, .startLine = 1, .endLine = 1} // ,
            << SourceLocation{.source = input, .startIndex = 18, .endIndex = 19, .startColumn = 19, .endColumn = 20, .startLine = 1, .endLine = 1} // b
            << SourceLocation{.source = input, .startIndex = 20, .endIndex = 23, .startColumn = 21, .endColumn = 24, .startLine = 1, .endLine = 1} // int
            << SourceLocation{.source = input, .startIndex = 23, .endIndex = 24, .startColumn = 24, .endColumn = 25, .startLine = 1, .endLine = 1} // )
            << SourceLocation{.source = input, .startIndex = 28, .endIndex = 29, .startColumn = 2, .endColumn = 3, .startLine = 2, .endLine = 2}  // {
            << SourceLocation{.source = input, .startIndex = 32, .endIndex = 38, .startColumn = 2, .endColumn = 8, .startLine = 3, .endLine = 3}  // return
            << SourceLocation{.source = input, .startIndex = 39, .endIndex = 40, .startColumn = 9, .endColumn = 10, .startLine = 3, .endLine = 3}  // a
            << SourceLocation{.source = input, .startIndex = 41, .endIndex = 42, .startColumn = 11, .endColumn = 12, .startLine = 3, .endLine = 3} // +
            << SourceLocation{.source = input, .startIndex = 43, .endIndex = 44, .startColumn = 13, .endColumn = 14, .startLine = 3, .endLine = 3} // b
            << SourceLocation{.source = input, .startIndex = 47, .endIndex = 48, .startColumn = 1, .endColumn = 2, .startLine = 4, .endLine = 4}  // }
            << SourceLocation{.source = input, .startIndex = 50, .endIndex = 50, .startColumn = 1, .endColumn = 1, .startLine = 5, .endLine = 5}; // EOL

        DiagnosticsBag diagnostics;

        auto startTime = std::chrono::high_resolution_clock::now();
        auto tokens = Lex(input, diagnostics);

        auto endTime = std::chrono::high_resolution_clock::now();
        auto elapsed_time_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        qDebug() << "Time: " << elapsed_time_ms << "ns";

        QCOMPARE(tokens.size(), expectedList.size());
        for (i32 i = 0; i < tokens.size(); i++)
        {
            auto index = tokens[i].locationIndex;
            auto& location = tokens.GetSourceLocation(index);

            QCOMPARE(location.startIndex, expectedList[i].startIndex);
            QCOMPARE(location.endIndex, expectedList[i].endIndex);
            QCOMPARE(location.startColumn, expectedList[i].startColumn);
            QCOMPARE(location.endColumn, expectedList[i].endColumn);
            QCOMPARE(location.startLine, expectedList[i].startLine);
            QCOMPARE(location.endLine, expectedList[i].endLine);
        }
    }
};

QTEST_MAIN(SourceLocationTests)
#include "SourceLocationTests.moc"
