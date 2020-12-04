#ifndef ACTIONCREATOR_H
#define ACTIONCREATOR_H

#include <QWidget>
#include <QComboBox>
#include <QSpinBox>
#include "input/Action.h"

#include "input/GlobalKeyboard.h"
#include "input/GlobalMouse.h"

namespace Ui {
class ActionCreator;
}

class ActionCreator : public QWidget
{
    Q_OBJECT

private:
    Ui::ActionCreator *ui;
    QComboBox *typeSelect;
    QComboBox *mouseEvents;
    QComboBox *keyboardEvents;

    QSpinBox *keyCode;
    QSpinBox *xPos;
    QSpinBox *yPos;
    QSpinBox *startTime;

    GlobalKeyboard *keyboard = nullptr;
    GlobalMouse *mouse = nullptr;

public:
    explicit ActionCreator(QWidget *parent = nullptr);
    ~ActionCreator();

    void fillWithAction(const Action* action);
    Action *makeAction();

    void setKeyboard(GlobalKeyboard *value);
    void setMouse(GlobalMouse *value);

private slots:
    void switchAction(const QString &name);
    void updateInputType();

private:
    void createLayout();
};

#endif // ACTIONCREATOR_H
