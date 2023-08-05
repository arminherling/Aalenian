#include <QTest>

#include <Compiler/Lexer.h>
#include <Compiler/SourceText.h>
#include <Compiler/Token.h>
#include <Compiler/TokenKind.h>

class LexerTests : public QObject
{
    Q_OBJECT

private slots:
    void SingleCharacter_data()
    {
        QTest::addColumn<QString>("input");
        QTest::addColumn<TokenKind>("expectedKind");
        QTest::addColumn<QString>("expectedLexeme");

        QTest::newRow("Plus") << "+" << TokenKind::Plus << "+";
        QTest::newRow("Minus") << "-" << TokenKind::Minus << "-";
        QTest::newRow("Star") << "*" << TokenKind::Star << "*";
        QTest::newRow("Slash") << "/" << TokenKind::Slash << "/";

        QTest::newRow("Dot") << "." << TokenKind::Dot << ".";
        QTest::newRow("Comma") << "," << TokenKind::Comma << ",";
        QTest::newRow("Equal") << "=" << TokenKind::Equal << "=";

        QTest::newRow("OpenParenthesis") << "(" << TokenKind::OpenParenthesis << "(";
        QTest::newRow("CloseParenthesis") << ")" << TokenKind::CloseParenthesis << ")";
        QTest::newRow("OpenBracket") << "{" << TokenKind::OpenBracket << "{";
        QTest::newRow("CloseBracket") << "}" << TokenKind::CloseBracket << "}";

        QTest::newRow("Unknown") << "$" << TokenKind::Unknown << "$";
        QTest::newRow("EOF") << "\0" << TokenKind::EndOfFile << "\0";
    }

    void SingleCharacter()
    {
        QFETCH(QString, input);
        QFETCH(TokenKind, expectedKind);
        QFETCH(QString, expectedLexeme);

        auto source = SourceText(input);
        auto lexer = Lexer(source);

        auto token = lexer.NextToken();

        QCOMPARE(token.kind, expectedKind);
        QCOMPARE(token.lexeme, expectedLexeme);
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

        auto source = SourceText(input);
        auto lexer = Lexer(source);

        auto token = lexer.NextToken();

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
        QTest::newRow("\\n return") << "\nreturn" << "return";
        QTest::newRow("_") << "_" << "_";
        QTest::newRow("_name") << " _name" << "_name";
        QTest::newRow("m_index") << "m_index" << "m_index";
        QTest::newRow("_10") << "_10" << "_10";
    }
    
    void Identifiers()
    {
        QFETCH(QString, input);
        QFETCH(QString, expectedLexeme);

        auto source = SourceText(input);
        auto lexer = Lexer(source);

        auto token = lexer.NextToken();

        QCOMPARE(token.kind, TokenKind::Identifier);
        QCOMPARE(token.lexeme, expectedLexeme);
    }

    void Numbers_data()
    {
        QTest::addColumn<QString>("input");
        QTest::addColumn<QString>("expectedLexeme");

        QTest::newRow("0") << "0" << "0";
        QTest::newRow("  1234 ") << "  1234 " << "1234";
        QTest::newRow("12.") << "12." << "12";
        QTest::newRow("12.34") << "12.34" << "12.34";
        QTest::newRow("12.34. ") << "12.34. " << "12.34";
        QTest::newRow(" 1234567890") << " 1234567890" << "1234567890";
    }
    
    void Numbers()
    {
        QFETCH(QString, input);
        QFETCH(QString, expectedLexeme);

        auto source = SourceText(input);
        auto lexer = Lexer(source);

        auto token = lexer.NextToken();

        QCOMPARE(token.kind, TokenKind::Number);
        QCOMPARE(token.lexeme, expectedLexeme);
    }
};

QTEST_MAIN(LexerTests)
#include "LexerTests.moc"
