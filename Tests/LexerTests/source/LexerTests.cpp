#include <AalTest.h>

#include <Syntax/Lexer.h>
#include <Syntax/Token.h>
#include <Syntax/TokenKind.h>
#include <Syntax/TokenBuffer.h>
#include <Text/SourceText.h>
#include <Text/SourceLocation.h>
#include <iostream>
#include <qdebug.h>
namespace
{
    void SingleCharacter(const QString& testName, const QString& input, TokenKind expectedKind)
    {
        auto startTime = std::chrono::high_resolution_clock::now();

        auto source = std::make_shared<SourceText>(input);
        DiagnosticsBag diagnostics;

        auto tokens = Lex(source, diagnostics);
        auto token = tokens[0];

        auto endTime = std::chrono::high_resolution_clock::now();
        std::cout << "   Lex(): " << Stringify(endTime - startTime).toStdString() << std::endl;

        AalTest::AreEqual(token.kind, expectedKind);
    }

    QList<std::tuple<QString, QString, TokenKind>> SingleCharacter_Data()
    {
        return {
            std::make_tuple(QString("Plus") , QString("+") , TokenKind::Plus),
            std::make_tuple(QString("Minus") , QString("-") , TokenKind::Minus),
            std::make_tuple(QString("Star") , QString("*") , TokenKind::Star),
            std::make_tuple(QString("Slash") , QString("/") , TokenKind::Slash),

            std::make_tuple(QString("Dot") , QString(".") , TokenKind::Dot),
            std::make_tuple(QString("Colon") , QString(":") , TokenKind::Colon),
            std::make_tuple(QString("DoubleColon") , QString("::") , TokenKind::DoubleColon),
            std::make_tuple(QString("Comma") , QString(",") , TokenKind::Comma),
            std::make_tuple(QString("Equal") , QString("=") , TokenKind::Equal),
            std::make_tuple(QString("Underscore") , QString("_") , TokenKind::Underscore),

            std::make_tuple(QString("OpenParenthesis") , QString("(") , TokenKind::OpenParenthesis),
            std::make_tuple(QString("CloseParenthesis") , QString(")") , TokenKind::CloseParenthesis),
            std::make_tuple(QString("OpenBracket") , QString("{") , TokenKind::OpenBracket),
            std::make_tuple(QString("CloseBracket") , QString("}") , TokenKind::CloseBracket),

            std::make_tuple(QString("Unknown") , QString("$") , TokenKind::Unknown),
            std::make_tuple(QString("EOF") , QString("") , TokenKind::EndOfFile),
            std::make_tuple(QString("EOF \\0") , QString("\0") , TokenKind::EndOfFile)
        };
    }

    void IgnoresWhitespaces(const QString& testName, const QString& input)
    {
        auto expectedToken = TokenKind::EndOfFile;
        auto startTime = std::chrono::high_resolution_clock::now();

        auto source = std::make_shared<SourceText>(input);
        DiagnosticsBag diagnostics;

        auto tokens = Lex(source, diagnostics);
        auto token = tokens[0];

        auto endTime = std::chrono::high_resolution_clock::now();
        std::cout << "   Lex(): " << Stringify(endTime - startTime).toStdString() << std::endl;
        AalTest::AreEqual(token.kind, TokenKind::EndOfFile);
    }

    QList<std::tuple<QString, QString>> IgnoresWhitespaces_Data()
    {
        return {
            std::make_tuple(QString("") , QString("")),
            std::make_tuple(QString(" ") , QString(" ")),
            std::make_tuple(QString("     ") , QString("     ")),
            std::make_tuple(QString("\\t") , QString("\t")),
            std::make_tuple(QString("\\r") , QString("\r")),
            std::make_tuple(QString("\\n") , QString("\n")),
            std::make_tuple(QString("\\r\\n") , QString("\r\n"))
        };
    }

    //    void Identifiers()
    //    {
    //        QFETCH(QString, input);
    //        QFETCH(QString, expectedLexeme);
    //
    //        auto startTime = std::chrono::high_resolution_clock::now();
    //
    //        auto source = std::make_shared<SourceText>(input);
    //        DiagnosticsBag diagnostics;
    //
    //        auto tokens = Lex(source, diagnostics);
    //        auto& token = tokens[0];
    //
    //        auto endTime = std::chrono::high_resolution_clock::now();
    //        auto elapsed_time_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
    //        qDebug() << "Time: " << elapsed_time_ms << "ns";
    //
    //        AalTest::AreEqual(token.kind, TokenKind::Identifier);
    //        auto& lexeme = tokens.GetLexeme(token.kindIndex);
    //        AalTest::AreEqual(lexeme, expectedLexeme);
    //    }
    //
    //    void Identifiers_Data()
    //    {
    //        QTest::addColumn<QString>("input");
    //        QTest::addColumn<QString>("expectedLexeme");
    //
    //        QTest::newRow("x") << "x" << "x";
    //        QTest::newRow("foo") << "foo" << "foo";
    //        QTest::newRow(" bar ") << " bar " << "bar";
    //        QTest::newRow("i32") << "i32" << "i32";
    //        QTest::newRow("use") << "use" << "use";
    //        QTest::newRow("enum") << "enum" << "enum";
    //        QTest::newRow("class") << "class" << "class";
    //        QTest::newRow("define") << "define" << "define";
    //        QTest::newRow("\\n return") << "\n return" << "return";
    //        QTest::newRow("_name") << " _name" << "_name";
    //        QTest::newRow("m_index") << "m_index" << "m_index";
    //        QTest::newRow("_10") << "_10" << "_10";
    //    }
    //
    //    void Numbers()
    //    {
    //        QFETCH(QString, input);
    //        QFETCH(QString, expectedLexeme);
    //
    //        auto startTime = std::chrono::high_resolution_clock::now();
    //
    //        auto source = std::make_shared<SourceText>(input);
    //        DiagnosticsBag diagnostics;
    //
    //        auto tokens = Lex(source, diagnostics);
    //        auto& token = tokens[0];
    //
    //        auto endTime = std::chrono::high_resolution_clock::now();
    //        auto elapsed_time_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
    //        qDebug() << "Time: " << elapsed_time_ms << "ns";
    //
    //        AalTest::AreEqual(token.kind, TokenKind::Number);
    //        auto& lexeme = tokens.GetLexeme(token.kindIndex);
    //        AalTest::AreEqual(lexeme, expectedLexeme);
    //    }
    //
    //    void Numbers_Data()
    //    {
    //        QTest::addColumn<QString>("input");
    //        QTest::addColumn<QString>("expectedLexeme");
    //
    //        QTest::newRow("0") << "0" << "0";
    //        QTest::newRow("  1234 ") << "  1234 " << "1234";
    //        QTest::newRow("  1_234 ") << "  1_234 " << "1_234";
    //        QTest::newRow("12.") << "12." << "12";
    //        QTest::newRow("12.34") << "12.34" << "12.34";
    //        QTest::newRow("1_2.3_4") << "1_2.3_4" << "1_2.3_4";
    //        QTest::newRow("12.34_") << "12.34_" << "12.34_";
    //        QTest::newRow("12.34. ") << "12.34. " << "12.34";
    //        QTest::newRow(" 1234567890") << " 1234567890" << "1234567890";
    //    }
    //
    //    void Strings()
    //    {
    //        QFETCH(QString, input);
    //        QFETCH(QString, expectedLexeme);
    //
    //        auto startTime = std::chrono::high_resolution_clock::now();
    //
    //        auto source = std::make_shared<SourceText>(input);
    //        DiagnosticsBag diagnostics;
    //
    //        auto tokens = Lex(source, diagnostics);
    //        auto& token = tokens[0];
    //
    //        auto endTime = std::chrono::high_resolution_clock::now();
    //        auto elapsed_time_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
    //        qDebug() << "Time: " << elapsed_time_ms << "ns";
    //
    //        AalTest::AreEqual(token.kind, TokenKind::String);
    //        auto& lexeme = tokens.GetLexeme(token.kindIndex);
    //        AalTest::AreEqual(lexeme, expectedLexeme);
    //    }
    //
    //    void Strings_Data()
    //    {
    //        QTest::addColumn<QString>("input");
    //        QTest::addColumn<QString>("expectedLexeme");
    //
    //        QTest::newRow(" \"\" ") << " \"\" " << "\"\"";
    //        QTest::newRow("  \"1234\" ") << "  \"1234\" " << "\"1234\"";
    //        QTest::newRow("\"string with whitespace\" ") << "\"string with whitespace\" " << "\"string with whitespace\"";
    //        QTest::newRow(" \"1234567890\"") << " \"1234567890\"" << "\"1234567890\"";
    //    }
    //
    //    void UnterminatedStrings()
    //    {
    //        QFETCH(QString, input);
    //        QFETCH(QString, expectedLexeme);
    //
    //        auto startTime = std::chrono::high_resolution_clock::now();
    //
    //        auto source = std::make_shared<SourceText>(input);
    //        DiagnosticsBag diagnostics;
    //
    //        auto tokens = Lex(source, diagnostics);
    //        auto& token = tokens[0];
    //
    //        AalTest::IsTrue(!diagnostics.Diagnostics().empty());
    //
    //        auto endTime = std::chrono::high_resolution_clock::now();
    //        auto elapsed_time_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
    //        qDebug() << "Time: " << elapsed_time_ms << "ns";
    //
    //        AalTest::AreEqual(token.kind, TokenKind::Error);
    //        auto& lexeme = tokens.GetLexeme(token.kindIndex);
    //        AalTest::AreEqual(lexeme, expectedLexeme);
    //    }
    //
    //    void UnterminatedStrings_Data()
    //    {
    //        QTest::addColumn<QString>("input");
    //        QTest::addColumn<QString>("expectedLexeme");
    //
    //        QTest::newRow(" \" ") << " \" " << "\" ";
    //        QTest::newRow("  \"1234 ") << "  \"1234 " << "\"1234 ";
    //        QTest::newRow("\"string with whitespace ") << "\"string with whitespace " << "\"string with whitespace ";
    //        QTest::newRow(" \"1234567890") << " \"1234567890" << "\"1234567890";
    //    }
    //
    //    void WholeInput()
    //    {
    //        QFETCH(QString, input);
    //        QFETCH(i32, tokenCount);
    //
    //        auto startTime = std::chrono::high_resolution_clock::now();
    //
    //        auto source = std::make_shared<SourceText>(input);
    //        DiagnosticsBag diagnostics;
    //
    //        auto tokens = Lex(source, diagnostics);
    //
    //        auto endTime = std::chrono::high_resolution_clock::now();
    //        auto elapsed_time_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
    //        qDebug() << "Time: " << elapsed_time_ms << "ns";
    //
    //        AalTest::IsTrue(diagnostics.Diagnostics().empty());
    //        AalTest::AreEqual(tokens.size(), tokenCount);
    //    }
    //
    //    void WholeInput_Data()
    //    {
    //        QTest::addColumn<QString>("input");
    //        QTest::addColumn<i32>("tokenCount");
    //
    //        QTest::newRow("") << "" << 1;
    //        QTest::newRow("name") << "name" << 2;
    //        QTest::newRow("use name") << "use name" << 3;
    //        QTest::newRow("return (x, y)") << "return (x, y)" << 7;
    //        //QTest::newRow("a = () => 3") << "a = () => 3" << 8;
    //        QTest::newRow("enum Value { A B = 5 C D }") << "enum Value { A B = 5 C D }" << 11;
    //        QTest::newRow("define sum(a int, b int) { return a + b }") << "define sum(a int, b int) { return a + b }" << 16;
    //    }
    //
    //    void OneMilLinesTime()
    //    {
    //#ifdef QT_DEBUG
    //        QSKIP("");
    //#endif
    //        auto combinedPath = QDir(QCoreApplication::applicationDirPath())
    //            .filePath(QString("../../Tests/LexerTests/data/oneMilLines.txt"));
    //        auto testFile = QDir::cleanPath(combinedPath);
    //
    //        QFile file(testFile);
    //        if (!file.open(QFile::ReadOnly | QFile::Text))
    //            AalTest::Fail();// ("Couldnt open file");
    //
    //        QString data = file.readAll();
    //
    //        auto source = std::make_shared<SourceText>(data);
    //        DiagnosticsBag diagnostics;
    //
    //        auto startTime = std::chrono::high_resolution_clock::now();
    //        auto tokens = Lex(source, diagnostics);
    //        auto endTime = std::chrono::high_resolution_clock::now();
    //
    //        auto elapsed_time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    //        qDebug() << elapsed_time_ms << "ms" << tokens.size() << "Tokens";
    //    }
}

TestSuite LexerTestsSuite()
{
    TestSuite suite{};
    suite.add(QString("SingleCharacter"), SingleCharacter, SingleCharacter_Data);
    suite.add(QString("IgnoresWhitespaces"), IgnoresWhitespaces, IgnoresWhitespaces_Data);
    //suite.add(QString("Identifiers"), Identifiers, Identifiers_Data);
    //suite.add(QString("Numbers"), Numbers, Numbers_Data);
    //suite.add(QString("Strings"), Strings, Strings_Data);
    //suite.add(QString("UnterminatedStrings"), UnterminatedStrings, UnterminatedStrings_Data);
    //suite.add(QString("WholeInput"), WholeInput, WholeInput_Data);
    //suite.add(QString("OneMilLinesTime"), OneMilLinesTime);

    return suite;
}
