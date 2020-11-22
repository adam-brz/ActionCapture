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
    timer = new QTimer(this);
    timer->start(200);

    mouse = DeviceFactory::makeMouse();
    mouse->setCallback([&](const KeyInfo &info){printMousePos(info);});

    keyboard = DeviceFactory::makeKeyboard();
    keyboard->setCallback([&](const KeyInfo &info){printKey(info.code, (int)info.status, info.time);});
}

EditorWindow::~EditorWindow()
{
    DeviceFactory::removeInstances();
    delete ui;
}

void EditorWindow::printMousePos(const KeyInfo &info)
{
    /*QScreen *screen = QApplication::primaryScreen();
    QCursor *cursor = new QCursor;*/
    //qDebug() << cursor->pos(screen);

    qDebug() << info.code  << " : " << (int)info.status << " : " << info.time;
}

void EditorWindow::printKey(int key, int status, int time)
{
    qDebug() <<  key  << " : " << status << " : " << time;
}

