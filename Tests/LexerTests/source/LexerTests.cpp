#include <AalTest.h>

#include <Syntax/Lexer.h>
#include <Syntax/Token.h>
#include <Syntax/TokenKind.h>
#include <Syntax/TokenBuffer.h>
#include <Text/SourceText.h>
#include <Text/SourceLocation.h>
#include <iostream>
#include <QDir>

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
        std::cout << "      Lex(): " << Stringify(endTime - startTime).toStdString() << std::endl;

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

    void IgnoresWhitespaces(const QString& input)
    {
        auto expectedToken = TokenKind::EndOfFile;
        auto startTime = std::chrono::high_resolution_clock::now();

        auto source = std::make_shared<SourceText>(input);
        DiagnosticsBag diagnostics;

        auto tokens = Lex(source, diagnostics);
        auto token = tokens[0];

        auto endTime = std::chrono::high_resolution_clock::now();
        std::cout << "      Lex(): " << Stringify(endTime - startTime).toStdString() << std::endl;

        AalTest::AreEqual(token.kind, TokenKind::EndOfFile);
    }

    QList<std::tuple<QString>> IgnoresWhitespaces_Data()
    {
        return {
            std::make_tuple(QString("")),
            std::make_tuple(QString(" ")),
            std::make_tuple(QString("     ")),
            std::make_tuple(QString("\t")),
            std::make_tuple(QString("\r")),
            std::make_tuple(QString("\n")),
            std::make_tuple(QString("\r\n"))
        };
    }

    void Identifiers(const QString& input, const QString& expectedLexeme)
    {
        auto startTime = std::chrono::high_resolution_clock::now();

        auto source = std::make_shared<SourceText>(input);
        DiagnosticsBag diagnostics;

        auto tokens = Lex(source, diagnostics);
        auto& token = tokens[0];

        auto endTime = std::chrono::high_resolution_clock::now();
        std::cout << "      Lex(): " << Stringify(endTime - startTime).toStdString() << std::endl;

        AalTest::AreEqual(token.kind, TokenKind::Identifier);
        auto& lexeme = tokens.GetLexeme(token.kindIndex);
        AalTest::AreEqual(lexeme, expectedLexeme);
    }

    QList<std::tuple<QString, QString>> Identifiers_Data()
    {
        return {
            std::make_tuple(QString("x"), QString("x")),
            std::make_tuple(QString("foo"), QString("foo")),
            std::make_tuple(QString(" bar "), QString("bar")),
            std::make_tuple(QString("i32"), QString("i32")),
            std::make_tuple(QString("use"), QString("use")),
            std::make_tuple(QString("enum"), QString("enum")),
            std::make_tuple(QString("class"), QString("class")),
            std::make_tuple(QString("define"), QString("define")),
            std::make_tuple(QString("\n return"), QString("return")),
            std::make_tuple(QString(" _name"), QString("_name")),
            std::make_tuple(QString("m_index"), QString("m_index")),
            std::make_tuple(QString("_10"), QString("_10"))
        };
    }

    void Numbers(const QString& input, const QString& expectedLexeme)
    {
        auto startTime = std::chrono::high_resolution_clock::now();

        auto source = std::make_shared<SourceText>(input);
        DiagnosticsBag diagnostics;

        auto tokens = Lex(source, diagnostics);
        auto& token = tokens[0];

        auto endTime = std::chrono::high_resolution_clock::now();
        std::cout << "      Lex(): " << Stringify(endTime - startTime).toStdString() << std::endl;

        AalTest::AreEqual(token.kind, TokenKind::Number);
        auto& lexeme = tokens.GetLexeme(token.kindIndex);
        AalTest::AreEqual(lexeme, expectedLexeme);
    }

    QList<std::tuple<QString, QString>> Numbers_Data()
    {
        return {
            std::make_tuple(QString("0"), QString("0")),
            std::make_tuple(QString("  1234 "), QString("1234")),
            std::make_tuple(QString("  1_234 "), QString("1_234")),
            std::make_tuple(QString("12."), QString("12")),
            std::make_tuple(QString("12.34"), QString("12.34")),
            std::make_tuple(QString("1_2.3_4"), QString("1_2.3_4")),
            std::make_tuple(QString("12.34_"), QString("12.34_")),
            std::make_tuple(QString("12.34. "), QString("12.34")),
            std::make_tuple(QString(" 1234567890"), QString("1234567890"))
        };
    }

    void Strings(const QString& input, const QString& expectedLexeme)
    {
        auto startTime = std::chrono::high_resolution_clock::now();

        auto source = std::make_shared<SourceText>(input);
        DiagnosticsBag diagnostics;

        auto tokens = Lex(source, diagnostics);
        auto& token = tokens[0];

        auto endTime = std::chrono::high_resolution_clock::now();
        std::cout << "      Lex(): " << Stringify(endTime - startTime).toStdString() << std::endl;

        AalTest::AreEqual(token.kind, TokenKind::String);
        auto& lexeme = tokens.GetLexeme(token.kindIndex);
        AalTest::AreEqual(lexeme, expectedLexeme);
    }

    QList<std::tuple<QString, QString>> Strings_Data()
    {
        return {
            std::make_tuple(QString(" \"\" "), QString("\"\"")),
            std::make_tuple(QString("  \"1234\" "), QString("\"1234\"")),
            std::make_tuple(QString("\"string with whitespace\" "), QString("\"string with whitespace\"")),
            std::make_tuple(QString(" \"1234567890\""), QString("\"1234567890\""))
        };
    }

    void UnterminatedStrings(const QString& input, const QString& expectedLexeme)
    {
        auto startTime = std::chrono::high_resolution_clock::now();

        auto source = std::make_shared<SourceText>(input);
        DiagnosticsBag diagnostics;

        auto tokens = Lex(source, diagnostics);
        auto& token = tokens[0];

        AalTest::IsTrue(!diagnostics.Diagnostics().empty());

        auto endTime = std::chrono::high_resolution_clock::now();
        std::cout << "      Lex(): " << Stringify(endTime - startTime).toStdString() << std::endl;

        AalTest::AreEqual(token.kind, TokenKind::Error);
        auto& lexeme = tokens.GetLexeme(token.kindIndex);
        AalTest::AreEqual(lexeme, expectedLexeme);
    }

    QList<std::tuple<QString, QString>> UnterminatedStrings_Data()
    {
        return {
            std::make_tuple(QString(" \" "), QString("\" ")),
            std::make_tuple(QString("  \"1234 "), QString("\"1234 ")),
            std::make_tuple(QString("\"string with whitespace "), QString("\"string with whitespace ")),
            std::make_tuple(QString(" \"1234567890"), QString("\"1234567890"))
        };
    }

    void WholeInput(QString input, i32 tokenCount)
    {
        auto startTime = std::chrono::high_resolution_clock::now();

        auto source = std::make_shared<SourceText>(input);
        DiagnosticsBag diagnostics;

        auto tokens = Lex(source, diagnostics);

        auto endTime = std::chrono::high_resolution_clock::now();
        std::cout << "      Lex(): " << Stringify(endTime - startTime).toStdString() << std::endl;

        AalTest::IsTrue(diagnostics.Diagnostics().empty());
        AalTest::AreEqual(tokens.size(), tokenCount);
    }

    QList<std::tuple<QString, i32>> WholeInput_Data()
    {
        return {
            std::make_tuple(QString(""), 1),
            std::make_tuple(QString("name"), 2),
            std::make_tuple(QString("use name"), 3),
            std::make_tuple(QString("return (x, y)"), 7),
            //std::make_tuple(QString("a = () => 3"), 8),
            std::make_tuple(QString("enum Value { A B = 5 C D }"), 11),
            std::make_tuple(QString("define sum(a int, b int) { return a + b }"), 16)
        };
    }

    void OneMilLinesTime()
    {
#ifdef QT_DEBUG
        AalTest::Skip();// ("");
#endif
        auto testFile = QDir::cleanPath(QString("../../Tests/LexerTests/data/oneMilLines.txt"));

        QFile file(testFile);
        if (!file.open(QFile::ReadOnly | QFile::Text))
            AalTest::Fail();// ("Couldnt open file");

        QString data = file.readAll();

        auto source = std::make_shared<SourceText>(data);
        DiagnosticsBag diagnostics;

        auto startTime = std::chrono::high_resolution_clock::now();
        auto tokens = Lex(source, diagnostics);

        auto endTime = std::chrono::high_resolution_clock::now();
        std::cout << "      Lex(): " << Stringify(endTime - startTime).toStdString() << std::endl;
    }
}

TestSuite LexerTestsSuite()
{
    TestSuite suite{};
    suite.add(QString("SingleCharacter"), SingleCharacter, SingleCharacter_Data);
    suite.add(QString("IgnoresWhitespaces"), IgnoresWhitespaces, IgnoresWhitespaces_Data);
    suite.add(QString("Identifiers"), Identifiers, Identifiers_Data);
    suite.add(QString("Numbers"), Numbers, Numbers_Data);
    suite.add(QString("Strings"), Strings, Strings_Data);
    suite.add(QString("UnterminatedStrings"), UnterminatedStrings, UnterminatedStrings_Data);
    suite.add(QString("WholeInput"), WholeInput, WholeInput_Data);
    suite.add(QString("OneMilLinesTime"), OneMilLinesTime);

    return suite;
}
