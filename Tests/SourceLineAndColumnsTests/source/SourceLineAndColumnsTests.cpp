#include <QTest>

#include <Compiler/Lexer.h>
#include <Compiler/LexerResult.h>
#include <Compiler/SourceText.h>
#include <Compiler/SourceLocation.h>
#include <Compiler/Token.h>
#include <Compiler/TokenKind.h>
#include <Compiler/SourceLineAndColumns.h>

Q_DECLARE_METATYPE(SourceLineAndColumns);
Q_DECLARE_METATYPE(QList<SourceLineAndColumns>);

class SourceLindAndColumnsTests : public QObject
{
    Q_OBJECT

private slots:
    void StartAndEndLineAndColumns1()
    {
        auto input = QString("(");
        auto expectedList = QList<SourceLineAndColumns>()
            << SourceLineAndColumns{.startLine = 1, .startColumn = 1, .endLine = 1, .endColumn = 1}
            << SourceLineAndColumns{.startLine = 1, .startColumn = 2, .endLine = 1, .endColumn = 2};

        auto source = SourceText(input);
        auto lexer = Lexer(source);

        auto result = lexer.Lex();

        QCOMPARE(result.tokens.size(), expectedList.size());
        for (int i = 0; i < result.tokens.size(); i++)
        {
            auto location = result.tokens[i].location;
            auto info = StartAndEndPositions(location.sourceText, location.firstIndex, location.lastIndex);

            QCOMPARE(info.startLine, expectedList[i].startLine);
            QCOMPARE(info.startColumn, expectedList[i].startColumn);
            QCOMPARE(info.endLine, expectedList[i].endLine);
            QCOMPARE(info.endColumn, expectedList[i].endColumn);
        }
    }

    void StartAndEndLineAndColumns2()
    {
        auto input = QString("define sum(a int, b int) \r\n {\r\n return a + b \r\n}\r\n");
        auto expectedList = QList<SourceLineAndColumns>()
            << SourceLineAndColumns{.startLine = 1, .startColumn = 1,  .endLine = 1, .endColumn = 6}  // define
            << SourceLineAndColumns{.startLine = 1, .startColumn = 8,  .endLine = 1, .endColumn = 10} // sum
            << SourceLineAndColumns{.startLine = 1, .startColumn = 11, .endLine = 1, .endColumn = 11} // (
            << SourceLineAndColumns{.startLine = 1, .startColumn = 12, .endLine = 1, .endColumn = 12} // a
            << SourceLineAndColumns{.startLine = 1, .startColumn = 14, .endLine = 1, .endColumn = 16} // int
            << SourceLineAndColumns{.startLine = 1, .startColumn = 17, .endLine = 1, .endColumn = 17} // ,
            << SourceLineAndColumns{.startLine = 1, .startColumn = 19, .endLine = 1, .endColumn = 19} // b
            << SourceLineAndColumns{.startLine = 1, .startColumn = 21, .endLine = 1, .endColumn = 23} // int
            << SourceLineAndColumns{.startLine = 1, .startColumn = 24, .endLine = 1, .endColumn = 24} // )
            << SourceLineAndColumns{.startLine = 2, .startColumn = 2,  .endLine = 2, .endColumn = 2}  // {
            << SourceLineAndColumns{.startLine = 3, .startColumn = 2,  .endLine = 3, .endColumn = 7}  // return
            << SourceLineAndColumns{.startLine = 3, .startColumn = 9,  .endLine = 3, .endColumn = 9}  // a
            << SourceLineAndColumns{.startLine = 3, .startColumn = 11, .endLine = 3, .endColumn = 11} // +
            << SourceLineAndColumns{.startLine = 3, .startColumn = 13, .endLine = 3, .endColumn = 13} // b
            << SourceLineAndColumns{.startLine = 4, .startColumn = 1,  .endLine = 4, .endColumn = 1}  // }
            << SourceLineAndColumns{.startLine = 5, .startColumn = 1,  .endLine = 5, .endColumn = 1}; // EOL

        auto source = SourceText(input);
        auto lexer = Lexer(source);

        auto result = lexer.Lex();

        QCOMPARE(result.tokens.size(), expectedList.size());
        for (int i = 0; i < result.tokens.size(); i++)
        {
            auto location = result.tokens[i].location;
            auto info = StartAndEndPositions(location.sourceText, location.firstIndex, location.lastIndex);

            QCOMPARE(info.startLine, expectedList[i].startLine);
            QCOMPARE(info.startColumn, expectedList[i].startColumn);
            QCOMPARE(info.endLine, expectedList[i].endLine);
            QCOMPARE(info.endColumn, expectedList[i].endColumn);
        }
    }
};

QTEST_MAIN(SourceLindAndColumnsTests)
#include "SourceLineAndColumnsTests.moc"
