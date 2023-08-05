#include <QTest>

#include <Compiler/Lexer.h>
#include <Compiler/SourceText.h>
#include <Compiler/Token.h>
#include <Compiler/TokenKind.h>

class LexerTests : public QObject
{
    Q_OBJECT

private slots:
    void Lexer_Lexes_SingleCharacter_data()
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

    void Lexer_Lexes_SingleCharacter()
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

    void Lexer_Ignores_Whitespaces_data()
    {
        QTest::addColumn<QString>("input");

        QTest::newRow("") << "";
        QTest::newRow(" ") << " ";
        QTest::newRow("     ") << "     ";
        QTest::newRow("t") << "\t";
        QTest::newRow("r") << "\r";
        QTest::newRow("n") << "\n";
        QTest::newRow("rn") << "\r\n";
    }

    void Lexer_Ignores_Whitespaces()
    {
        QFETCH(QString, input);

        auto source = SourceText(input);
        auto lexer = Lexer(source);

        auto token = lexer.NextToken();

        QCOMPARE(token.kind, TokenKind::EndOfFile);
    }
};

QTEST_MAIN(LexerTests)
#include "LexerTests.moc"
