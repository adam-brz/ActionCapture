#include "editorwindow.h"
#include "ui_editorwindow.h"

#include "input/DeviceFactory.h"

#include <QKeyEvent>
#include <QEvent>
#include <QScreen>
#include <QCursor>
#include <QtDebug>

EditorWindow::EditorWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::EditorWindow)
{
    ui->setupUi(this);

    mouse = DeviceFactory::makeMouse();
    mouse->setCallback([&](const MouseEvent &event){mouseEvent(event);});

    keyboard = DeviceFactory::makeKeyboard();
    keyboard->setCallback([&](const KeyboardEvent &event){kbEvent(event);});

    /*QTimer::singleShot(2000, [&](){
        MouseEvent ev;
        ev.type = MouseEventType::MOVE;
        ev.point = Point{100, 100};
        mouse->sendInput(ev);
    });*/
}

EditorWindow::~EditorWindow()
{
    DeviceFactory::removeInstances();
    delete ui;
}

void EditorWindow::kbEvent(const KeyboardEvent &event)
{
    qDebug() << "Key: " << event.code << ": " << (int)(event.status);
}

void EditorWindow::mouseEvent(const MouseEvent &event)
{
    qDebug() << "Mouse: " << QPoint(event.point.x, event.point.y)
                << ": " << (int)(event.key)
                << ": " << (int)(event.type);
}
