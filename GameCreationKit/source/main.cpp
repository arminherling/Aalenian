#include "GameCreationKit.h"
#include <QtWidgets/QApplication>

#include "TokenListView.h"
#include <Compiler/SourceText.h>
#include <Compiler/Lexer.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //GameCreationKit w;
    TokenListView w;

    auto input = QString("define sum(a int, b int) \r\n {\r\n return a + b \r\n}\r\n");

    auto source = SourceText(input);
    auto lexer = Lexer(source);

    auto result = lexer.Lex();

    //w.setTokens(QList<Token>() << result.tokens[9]);
    w.setTokens(result.tokens);

    w.show();
    return a.exec();
}
