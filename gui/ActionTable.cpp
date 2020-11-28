#include "ActionTable.h"
#include <QMenu>
#include <QHeaderView>

ActionTable::ActionTable(QWidget *parent) :
    QTableWidget(parent)
{
    setColumnCount(2);
    setEditTriggers(EditTriggers());

    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);

    QHeaderView *header = horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);

    setHorizontalHeaderLabels({tr("Action"),
                              tr("Start time [ms] (from last)")});

    actionInvoker.setSingleShot(true);
    connect(&actionInvoker, &QTimer::timeout, this, &ActionTable::invokeActions);
}

void ActionTable::addAction(Action *action, int index)
{
    actions.append(action);
    index = (index < 0) ? rowCount() : index;
    insertRow(index);

    QTableWidgetItem *name = new QTableWidgetItem(QString::fromStdString(action->name()));
    setItem(index, 0, name);

    QTableWidgetItem *time = new QTableWidgetItem(QString("%1").arg(action->getStartTime()));
    setItem(index, 1, time);
}

void ActionTable::runActions()
{
    int currentIndex = current();

    if(size() < 0)
        return;

    if(currentIndex < 0)
    {
        select(0);
        currentIndex = 0;
    }

    actionInvoker.start(actions[currentIndex]->getStartTime());
}

void ActionTable::stopRunning()
{
    actionInvoker.stop();
}

void ActionTable::select(int index)
{
    selectRow(index);
}

int ActionTable::current()
{
    return currentRow();
}

int ActionTable::size()
{
    return actions.size();
}

void ActionTable::mousePressEvent(QMouseEvent *event)
{
    // TODO: move to new QTabWidget sub-class
    if(event->buttons() & Qt::RightButton)
    {

        QMenu *contextMenu = new QMenu(this);

        contextMenu->addAction("Insert Above",
                               [=](){});

        contextMenu->addAction("Insert Below",
                               [=](){});

        contextMenu->addSeparator();

        contextMenu->addAction("Delete",
                               [=](){});

        contextMenu->popup(event->globalPos());

    }

    QTableWidget::mousePressEvent(event);
}

void ActionTable::invokeActions()
{
    int currentIndex = current();
    actions[currentIndex]->run();

    emit runUpdated(currentIndex);

    if(currentIndex < rowCount() - 1)
    {
        select(currentIndex + 1);
        actionInvoker.start(actions[currentIndex + 1]->getStartTime());
    }
}
