#ifndef ACTIONTABLE_H
#define ACTIONTABLE_H

#include <QWidget>
#include <QTableWidget>

#include <QList>
#include <QTimer>

#include "input/GlobalMouse.h"
#include "input/GlobalKeyboard.h"
#include "input/Action.h"

#include "toolbox/Savable.h"

class ActionTable : public QTableWidget, public Savable
{
    Q_OBJECT

private:
    QList<Action*> actions;

    GlobalMouse *mouse = nullptr;
    GlobalKeyboard *keyboard = nullptr;

    QTimer actionInvoker;
    QPoint clicked;

public:
    explicit ActionTable(QWidget *parent = nullptr);
    virtual ~ActionTable();

    void setMouse(GlobalMouse *value);
    void setKeyboard(GlobalKeyboard *value);

    void addAction(Action* action, int index = -1);
    void removeAction(int index);
    void clearActions();

    void runActions();
    void stopRunning();

    void select(int index);
    int current();
    int size();

    virtual unsigned char typeID() const override;
    virtual SavableData *save() const override;
    virtual bool restore(SavableData *data) override;

protected:
    void mousePressEvent(QMouseEvent *event) override;

private slots:
    void invokeActions();

signals:
    void runUpdated(int);
};

#endif // ACTIONTABLE_H
