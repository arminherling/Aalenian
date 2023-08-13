#include "TokenListView.h"

#include <QStandardItemModel>
#include <QHeaderView>

TokenListView::TokenListView(QWidget* parent)
    : QTableView(parent)
    , model(new QStandardItemModel(this))
{
    setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
    setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
    setFocusPolicy(Qt::NoFocus);
    setShowGrid(false);
    verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    verticalHeader()->setDefaultSectionSize(0);

    setModel(model);

    setMinimumSize(800, 500);
}

void TokenListView::setTokens(const QList<Token>& tokens)
{
    model->clear();
    model->setHorizontalHeaderLabels(QStringList() << QString("Lexeme")  << QString("Kind") << QString("Location"));
    for (int i = 0; i < tokens.length(); i++)
    {
        auto& token = tokens.at(i);

        model->setItem(i, 0, new QStandardItem(token.lexeme));
        model->setItem(i, 1, new QStandardItem(Stringify(token.kind)));
        model->setItem(i, 2, new QStandardItem(token.location.Stringify()));
    }
    resizeColumnsToContents();
}
