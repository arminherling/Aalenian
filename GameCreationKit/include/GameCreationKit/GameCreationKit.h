#pragma once

#include <QtWidgets/QMainWindow>

#include <QTextEdit>
#include "TokenListView.h"

class GameCreationKit : public QMainWindow
{
    Q_OBJECT

public:
    GameCreationKit(QWidget *parent = nullptr);
    virtual ~GameCreationKit() = default;

private:
    QTextEdit* textEdit;
    TokenListView* tokenList;

    void onTextChanged();
};
