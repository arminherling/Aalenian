#include <QTest>

#include <Compiler/Lexer.h>
#include <Compiler/SourceText.h>

class LexerTests :public QObject
{
    Q_OBJECT

private slots:
    void Lexer_Lexes_SingleCharacter()
    {
        auto source = new SourceText(QString("+"));

        QFAIL("test");
    }
};

QTEST_MAIN(LexerTests)
#include "LexerTests.moc"