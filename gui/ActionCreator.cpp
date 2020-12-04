#include "ActionCreator.h"
#include "ui_ActionCreator.h"

#include "input/KeyboardAction.h"
#include "input/MouseAction.h"

#include "input/KeyboardEvent.h"
#include "input/MouseEvent.h"
#include <QLabel>

ActionCreator::ActionCreator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ActionCreator)
{
    ui->setupUi(this);

    typeSelect = new QComboBox(this);
    typeSelect->addItem("Keyboard");
    typeSelect->addItem("Mouse");

    mouseEvents = new QComboBox(this);
    for(const auto& name: mouseActions())
        mouseEvents->addItem(QString::fromStdString(name));

    keyboardEvents = new QComboBox(this);
    for(const auto& name: keyboardActions())
        keyboardEvents->addItem(QString::fromStdString(name));

    connect(typeSelect, &QComboBox::currentTextChanged,
            this, &ActionCreator::switchAction);

    connect(mouseEvents, &QComboBox::currentTextChanged,
            [=](){updateInputType();});

    connect(keyboardEvents, &QComboBox::currentTextChanged,
            [=](){updateInputType();});

    keyCode = new QSpinBox(this);
    keyCode->setRange(0, 999999);

    xPos = new QSpinBox(this);
    xPos->setRange(0, 999999);

    yPos = new QSpinBox(this);
    yPos->setRange(0, 999999);

    startTime = new QSpinBox(this);
    startTime->setRange(0, 999999);

    typeSelect->setCurrentText("Keyboard");
    switchAction(typeSelect->currentText());
    createLayout();
}

ActionCreator::~ActionCreator()
{
    delete ui;
}

void ActionCreator::setKeyboard(GlobalKeyboard *value)
{
    keyboard = value;
}

void ActionCreator::setMouse(GlobalMouse *value)
{
    mouse = value;
}

void ActionCreator::fillWithAction(const Action *action)
{
    if(!action)
        return;

    if(dynamic_cast<const KeyboardAction*>(action))
    {
        const KeyboardAction *keyboardAction = dynamic_cast<const KeyboardAction*>(action);
        typeSelect->setCurrentText("Keyboard");

        keyCode->setValue(keyboardAction->readEvent().code);
        keyboardEvents->setCurrentText(QString::fromStdString(to_string(
                                       keyboardAction->readEvent().status)));

    }
    else if (dynamic_cast<const MouseAction*>(action))
    {
        const MouseAction *mouseAction = dynamic_cast<const MouseAction*>(action);
        typeSelect->setCurrentText("Mouse");
        mouseEvents->setCurrentText(QString::fromStdString(
                                    to_string(mouseAction->readEvent().type)));
        keyCode->setValue(mouseAction->readEvent().key);

        xPos->setValue(mouseAction->readEvent().point.x);
        yPos->setValue(mouseAction->readEvent().point.y);
    }

    startTime->setValue(action->getStartTime());
    switchAction(typeSelect->currentText());
}

Action *ActionCreator::makeAction()
{
    bool isKeyboardAction = typeSelect->currentText() == "Keyboard";
    Action *action;

    if(isKeyboardAction)
    {
        KeyboardEvent event;
        event.code = keyCode->value();
        event.status = to_keyStatus(keyboardEvents->currentText().toStdString());
        action = new KeyboardAction(keyboard, event);
    }
    else
    {
        MouseEvent event;
        event.key = keyCode->value();
        event.type = to_mouseEvent(mouseEvents->currentText().toStdString());
        event.point = Point(xPos->value(), yPos->value());
        action = new MouseAction(mouse, event);
    }

    action->setStartTime(startTime->value());
    return action;
}

void ActionCreator::switchAction(const QString &name)
{
    if(name == "Keyboard")
    {
        mouseEvents->setVisible(false);
        keyboardEvents->setVisible(true);
    }
    else
    {
        mouseEvents->setVisible(true);
        keyboardEvents->setVisible(false);
    }

    updateInputType();
}

void ActionCreator::updateInputType()
{
    xPos->setVisible(false);
    yPos->setVisible(false);
    keyCode->setVisible(true);

    if(typeSelect->currentText() != "Keyboard")
    {
        xPos->setVisible(true);
        yPos->setVisible(true);

        if(mouseEvents->currentText().toStdString() ==
                to_string(MouseEventType::MOVE))
        {
            keyCode->setVisible(false);
        }
    }
}

void ActionCreator::createLayout()
{
    ui->layout->addWidget(new QLabel(tr("Type:"), this), 0, 0);
    ui->layout->addWidget(typeSelect, 1, 0);

    ui->layout->addWidget(new QLabel(tr("Action:"), this), 0, 1);
    ui->layout->addWidget(mouseEvents, 1, 1);
    ui->layout->addWidget(keyboardEvents, 1, 1);

    ui->layout->addWidget(new QLabel(tr("Key:"), this), 0, 2);
    ui->layout->addWidget(new QLabel(tr("x:"), this), 0, 3);
    ui->layout->addWidget(new QLabel(tr("y:"), this), 0, 4);

    ui->layout->addWidget(keyCode, 1, 2);
    ui->layout->addWidget(xPos, 1, 3);
    ui->layout->addWidget(yPos, 1, 4);

    ui->layout->addWidget(new QLabel(tr("Start time [ms]:"), this), 0, 5);
    ui->layout->addWidget(startTime, 1, 5);
}


