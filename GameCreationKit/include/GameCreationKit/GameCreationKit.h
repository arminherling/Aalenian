#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GameCreationKit.h"

class GameCreationKit : public QMainWindow
{
    Q_OBJECT

public:
    GameCreationKit(QWidget *parent = nullptr);
    ~GameCreationKit();

private:
    Ui::GameCreationKitClass ui;
};
