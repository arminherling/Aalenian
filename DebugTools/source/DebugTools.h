#pragma once

#include <QtWidgets/QMainWindow>

#include <QTextEdit>
#include "TokenListView.h"

class DebugTools : public QMainWindow
{
    Q_OBJECT

public:
    DebugTools(QWidget *parent = nullptr);
    virtual ~DebugTools() = default;

private:
    QTextEdit* textEdit;
    TokenListView* tokenList;

    void onTextChanged();
};
