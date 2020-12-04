#include "ActionTable.h"
#include "toolbox/SavableData.h"

#include <QMenu>
#include <QHeaderView>

#include <algorithm>

#include "input/KeyboardAction.h"
#include "input/MouseAction.h"

ActionTable::ActionTable(QWidget *parent) :
    QTableWidget(parent)
{
    setColumnCount(2);
    setEditTriggers(EditTriggers());

    setSelectionMode(QAbstractItemView::ExtendedSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);

    QHeaderView *header = horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);

    setHorizontalHeaderLabels({tr("Action"),
                              tr("Start time [ms] (from last)")});

    actionInvoker.setSingleShot(true);
    connect(&actionInvoker, &QTimer::timeout, this, &ActionTable::invokeActions);
}

ActionTable::~ActionTable()
{
    clearActions();
}

void ActionTable::clearActions()
{
    for(auto &action: actions)
        delete action;

    actions.clear();

    QAbstractItemModel *model = this->model();
    model->removeRows(0, model->rowCount());
}

void ActionTable::setMouse(GlobalMouse *value)
{
    mouse = value;
}

void ActionTable::setKeyboard(GlobalKeyboard *value)
{
    keyboard = value;
}

void ActionTable::addAction(Action *action, int index)
{
    index = (index < 0) ? rowCount() : index;

    insertRow(index);
    actions.insert(index, action);

    QTableWidgetItem *name = new QTableWidgetItem(QString::fromStdString(action->name()));
    setItem(index, 0, name);

    QTableWidgetItem *time = new QTableWidgetItem(QString("%1").arg(action->getStartTime()));
    setItem(index, 1, time);
}

void ActionTable::removeAction(int index)
{
    if(index >= 0 && index < this->size())
    {
        delete actions[index];

        removeRow(index);
        actions.removeAt(index);
    }
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

unsigned char ActionTable::typeID() const
{
   return 0;
}

SavableData *ActionTable::save() const
{
    SavableData *data = Savable::save();

    for(const auto& action : actions) {
        data->add(*action->save());
    }

    return data;
}

bool ActionTable::restore(SavableData *data)
{
    if(!Savable::restore(data))
        return false;

    Action *action;
    clearActions();

    while(!data->atEnd()) {
        switch((data->getRaw()[data->pos()])) {
            case KEYBOAD_ACTION_ID:
                action = new KeyboardAction(keyboard);
                break;
            case MOUSE_ACTION_ID:
                action = new MouseAction(mouse);
                break;
            default:
                return false;
        }

        action->restore(data);
        addAction(action);
    }

    return true;
}

void ActionTable::mousePressEvent(QMouseEvent *event)
{
    applyEditIfNeeded();

    if(event->buttons() & Qt::RightButton)
    {
        QMenu *contextMenu = new QMenu(this);

        contextMenu->addSeparator();
        contextMenu->addAction("Delete", this, &ActionTable::removeSelected);

        contextMenu->popup(event->globalPos());
    }

    QTableWidget::mousePressEvent(event);
}

void ActionTable::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        int row = rowAt(event->pos().y());
        editRow(row);
    }

    QTableWidget::mouseDoubleClickEvent(event);
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

void ActionTable::removeSelected()
{
    QList<int> selected = getSelected();

    for(const auto &idx: selected)
        removeAction(idx);
}

QList<int> ActionTable::getSelected()
{
    QList<int> rows;

    for(const auto& idx : selectionModel()->selectedRows())
        rows.append(idx.row());

    std::sort(rows.rbegin(), rows.rend());
    return rows;
}

void ActionTable::applyEditIfNeeded()
{
    if(creator)
    {
        Action *newAction = creator->makeAction();

        creator->deleteLater();
        creator = nullptr;

        removeAction(editedRow);
        addAction(newAction, editedRow);
    }
}

void ActionTable::editRow(int row)
{
    if(itemAt(row, 0) && itemAt(row, 1)) {
        item(row, 0)->setText("");
        item(row, 1)->setText("");
    }

    creator = new ActionCreator(this);

    if(row < actions.size())
        creator->fillWithAction(actions[row]);

    creator->setKeyboard(keyboard);
    creator->setMouse(mouse);

    setCellWidget(row, 0, creator);
    setRowHeight(row, creator->sizeHint().height());

    editedRow = row;
}
