#include "GameCreationKit.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameCreationKit w;
    w.show();
    return a.exec();
}
