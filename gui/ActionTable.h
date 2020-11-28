#ifndef ACTIONTABLE_H
#define ACTIONTABLE_H

#include <QWidget>
#include <QTableWidget>

#include <QList>
#include <QTimer>

#include "input/Action.h"

class ActionTable : public QTableWidget
{
    Q_OBJECT

private:
    QList<Action*> actions;
    QTimer actionInvoker;

public:
    explicit ActionTable(QWidget *parent = nullptr);

    void addAction(Action* action, int index = -1);
    void runActions();
    void stopRunning();

    void select(int index);
    int current();
    int size();

protected:
    void mousePressEvent(QMouseEvent *event) override;

private slots:
    void invokeActions();

signals:
    void runUpdated(int);
};

#endif // ACTIONTABLE_H
