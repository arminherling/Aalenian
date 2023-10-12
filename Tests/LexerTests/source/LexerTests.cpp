#include <QTest>

#include <Compiler/Lexer.h>
#include <Compiler/SourceText.h>
#include <Compiler/SourceLocation.h>
#include <Compiler/Token.h>
#include <Compiler/TokenKind.h>
#include <chrono>

#include <Compiler/TokenBuffer.h>

class LexerTests : public QObject
{
    Q_OBJECT

private slots:
    void SingleCharacter_data()
    {
        QTest::addColumn<QString>("input");
        QTest::addColumn<TokenKind>("expectedKind");

        QTest::newRow("Plus") << QString("+") << TokenKind::Plus;
        QTest::newRow("Minus") << QString("-") << TokenKind::Minus;
        QTest::newRow("Star") << QString("*") << TokenKind::Star;
        QTest::newRow("Slash") << QString("/") << TokenKind::Slash;

        QTest::newRow("Dot") << QString(".") << TokenKind::Dot;
        QTest::newRow("Comma") << QString(",") << TokenKind::Comma;
        QTest::newRow("Equal") << QString("=") << TokenKind::Equal;

        QTest::newRow("OpenParenthesis") << QString("(") << TokenKind::OpenParenthesis;
        QTest::newRow("CloseParenthesis") << QString(")") << TokenKind::CloseParenthesis;
        QTest::newRow("OpenBracket") << QString("{") << TokenKind::OpenBracket;
        QTest::newRow("CloseBracket") << QString("}") << TokenKind::CloseBracket;

        QTest::newRow("Unknown") << QString("$") << TokenKind::Unknown;
        QTest::newRow("EOF") << QString("") << TokenKind::EndOfFile;
        QTest::newRow("EOF \\0") << QString("\0") << TokenKind::EndOfFile;
    }

    void SingleCharacter()
    {
        QFETCH(QString, input);
        QFETCH(TokenKind, expectedKind);

        auto startTime = std::chrono::high_resolution_clock::now();

        auto source = std::make_shared<SourceText>(input);
        V2::DiagnosticsBag diagnostics;

        auto tokens = V2::Lex(source, diagnostics);
        auto& token = tokens[0];

        auto endTime = std::chrono::high_resolution_clock::now();
        double elapsed_time_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        qDebug() << "Time: " << elapsed_time_ms << "ns";

        QCOMPARE(token.kind, expectedKind);
    }

    void IgnoresWhitespaces_data()
    {
        QTest::addColumn<QString>("input");

        QTest::newRow("") << "";
        QTest::newRow(" ") << " ";
        QTest::newRow("     ") << "     ";
        QTest::newRow("\\t") << "\t";
        QTest::newRow("\\r") << "\r";
        QTest::newRow("\\n") << "\n";
        QTest::newRow("\\r\\n") << "\r\n";
    }

    void IgnoresWhitespaces()
    {
        QFETCH(QString, input);

        auto startTime = std::chrono::high_resolution_clock::now();

        auto source = std::make_shared<SourceText>(input);
        V2::DiagnosticsBag diagnostics;

        auto tokens = V2::Lex(source, diagnostics);
        auto& token = tokens[0];

        auto endTime = std::chrono::high_resolution_clock::now();
        double elapsed_time_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        qDebug() << "Time: " << elapsed_time_ms << "ns";

        QCOMPARE(token.kind, TokenKind::EndOfFile);
    }

    void Identifiers_data()
    {
        QTest::addColumn<QString>("input");
        QTest::addColumn<QString>("expectedLexeme");

        QTest::newRow("x") << "x" << "x";
        QTest::newRow("foo") << "foo" << "foo";
        QTest::newRow(" bar ") << " bar " << "bar";
        QTest::newRow("i32") << "i32" << "i32";
        QTest::newRow("use") << "use" << "use";
        QTest::newRow("enum") << "enum" << "enum";
        QTest::newRow("class") << "class" << "class";
        QTest::newRow("define") << "define" << "define";
        QTest::newRow("\\n return") << "\n return" << "return";
        QTest::newRow("_") << "_" << "_";
        QTest::newRow("_name") << " _name" << "_name";
        QTest::newRow("m_index") << "m_index" << "m_index";
        QTest::newRow("_10") << "_10" << "_10";
    }

    void Identifiers()
    {
        QFETCH(QString, input);
        QFETCH(QString, expectedLexeme);

        auto startTime = std::chrono::high_resolution_clock::now();

        auto source = std::make_shared<SourceText>(input);
        V2::DiagnosticsBag diagnostics;

        auto tokens = V2::Lex(source, diagnostics);
        auto& token = tokens[0];

        auto endTime = std::chrono::high_resolution_clock::now();
        double elapsed_time_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        qDebug() << "Time: " << elapsed_time_ms << "ns";

        QCOMPARE(token.kind, TokenKind::Identifier);
        auto& lexeme = tokens.GetLexeme(token.kindIndex);
        QCOMPARE(lexeme, expectedLexeme);
    }

    void Numbers_data()
    {
        QTest::addColumn<QString>("input");
        QTest::addColumn<QString>("expectedLexeme");

        QTest::newRow("0") << "0" << "0";
        QTest::newRow("  1234 ") << "  1234 " << "1234";
        QTest::newRow("  1_234 ") << "  1_234 " << "1_234";
        QTest::newRow("12.") << "12." << "12";
        QTest::newRow("12.34") << "12.34" << "12.34";
        QTest::newRow("1_2.3_4") << "1_2.3_4" << "1_2.3_4";
        QTest::newRow("12.34_") << "12.34_" << "12.34_";
        QTest::newRow("12.34. ") << "12.34. " << "12.34";
        QTest::newRow(" 1234567890") << " 1234567890" << "1234567890";
    }

    void Numbers()
    {
        QFETCH(QString, input);
        QFETCH(QString, expectedLexeme);

        auto startTime = std::chrono::high_resolution_clock::now();

        auto source = std::make_shared<SourceText>(input);
        V2::DiagnosticsBag diagnostics;

        auto tokens = V2::Lex(source, diagnostics);
        auto& token = tokens[0];

        auto endTime = std::chrono::high_resolution_clock::now();
        double elapsed_time_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        qDebug() << "Time: " << elapsed_time_ms << "ns";

        QCOMPARE(token.kind, TokenKind::Number);
        auto& lexeme = tokens.GetLexeme(token.kindIndex);
        QCOMPARE(lexeme, expectedLexeme);
    }

    void Strings_data()
    {
        QTest::addColumn<QString>("input");
        QTest::addColumn<QString>("expectedLexeme");

        QTest::newRow(" \"\" ") << " \"\" " << "\"\"";
        QTest::newRow("  \"1234\" ") << "  \"1234\" " << "\"1234\"";
        QTest::newRow("\"string with whitespace\" ") << "\"string with whitespace\" " << "\"string with whitespace\"";
        QTest::newRow(" \"1234567890\"") << " \"1234567890\"" << "\"1234567890\"";
    }

    void Strings()
    {
        QFETCH(QString, input);
        QFETCH(QString, expectedLexeme);

        auto startTime = std::chrono::high_resolution_clock::now();

        auto source = std::make_shared<SourceText>(input);
        V2::DiagnosticsBag diagnostics;

        auto tokens = V2::Lex(source, diagnostics);
        auto& token = tokens[0];

        auto endTime = std::chrono::high_resolution_clock::now();
        double elapsed_time_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        qDebug() << "Time: " << elapsed_time_ms << "ns";

        QCOMPARE(token.kind, TokenKind::String);
        auto& lexeme = tokens.GetLexeme(token.kindIndex);
        QCOMPARE(lexeme, expectedLexeme);
    }

    void UnterminatedStrings_data()
    {
        QTest::addColumn<QString>("input");
        QTest::addColumn<QString>("expectedLexeme");

        QTest::newRow(" \" ") << " \" " << "\" ";
        QTest::newRow("  \"1234 ") << "  \"1234 " << "\"1234 ";
        QTest::newRow("\"string with whitespace ") << "\"string with whitespace " << "\"string with whitespace ";
        QTest::newRow(" \"1234567890") << " \"1234567890" << "\"1234567890";
    }

    void UnterminatedStrings()
    {
        QFETCH(QString, input);
        QFETCH(QString, expectedLexeme);

        auto startTime = std::chrono::high_resolution_clock::now();

        auto source = std::make_shared<SourceText>(input);
        V2::DiagnosticsBag diagnostics;

        auto tokens = V2::Lex(source, diagnostics);
        auto& token = tokens[0];

        QVERIFY(!diagnostics.Diagnostics().empty());

        auto endTime = std::chrono::high_resolution_clock::now();
        double elapsed_time_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        qDebug() << "Time: " << elapsed_time_ms << "ns";

        QCOMPARE(token.kind, TokenKind::Error);
        auto& lexeme = tokens.GetLexeme(token.kindIndex);
        QCOMPARE(lexeme, expectedLexeme);
    }

    void WholeInput_data()
    {
        QTest::addColumn<QString>("input");
        QTest::addColumn<int>("tokenCount");

        QTest::newRow("") << "" << 1;
        QTest::newRow("name") << "name" << 2;
        QTest::newRow("use name") << "use name" << 3;
        QTest::newRow("return (x, y)") << "return (x, y)" << 7;
        //QTest::newRow("a = () => 3") << "a = () => 3" << 8;
        QTest::newRow("enum Value { A B = 5 C D }") << "enum Value { A B = 5 C D }" << 11;
        QTest::newRow("define sum(a int, b int) { return a + b }") << "define sum(a int, b int) { return a + b }" << 16;
    }

    void WholeInput()
    {
        QFETCH(QString, input);
        QFETCH(int, tokenCount);

        auto startTime = std::chrono::high_resolution_clock::now();

        auto source = std::make_shared<SourceText>(input);
        V2::DiagnosticsBag diagnostics;

        auto tokens = V2::Lex(source, diagnostics);

        auto endTime = std::chrono::high_resolution_clock::now();
        double elapsed_time_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        qDebug() << "Time: " << elapsed_time_ms << "ns";

        QVERIFY(diagnostics.Diagnostics().empty());
        QCOMPARE(tokens.size(), tokenCount);
    }

    void OneMilLocTime()
    {
#ifdef QT_DEBUG
        QSKIP("");
#endif
        auto combinedPath = QDir(QCoreApplication::applicationDirPath())
            .filePath(QString("../../Tests/LexerTests/data/oneMilLines.txt"));
        auto testFile = QDir::cleanPath(combinedPath);

        QFile file(testFile);
        if (!file.open(QFile::ReadOnly | QFile::Text))
            QFAIL("Couldnt open file");

        QString data = file.readAll();

        auto source = std::make_shared<SourceText>(data);
        V2::DiagnosticsBag diagnostics;

        auto startTime = std::chrono::high_resolution_clock::now();
        auto tokens = V2::Lex(source, diagnostics);
        auto endTime = std::chrono::high_resolution_clock::now();

        double elapsed_time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
        qDebug() << elapsed_time_ms << "ms" << tokens.size() << "Tokens";
    }
};

QTEST_MAIN(LexerTests)
#include "LexerTests.moc"
