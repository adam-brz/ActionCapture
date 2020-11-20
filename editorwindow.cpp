#include "editorwindow.h"
#include "ui_editorwindow.h"

#include "input/win/GlobalWinMouse.h"

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

    mouse = GlobalMouse::instance();
    keyboard = GlobalKeyboard::instance();
    keyboard->setCallback([&](const KeyInfo &info){printKey(info.code, (int)info.status, info.time);});

    connect(timer, &QTimer::timeout, this, &EditorWindow::printMousePos);
}

EditorWindow::~EditorWindow()
{
    keyboard->removeInstance();
    mouse->removeInstance();
    delete ui;
}

void EditorWindow::keyPressEvent(QKeyEvent *event)
{
   // qDebug() << event->timestamp() << " : " << Qt::Key(event->key()) << " : " << int(event->key());
}

void EditorWindow::printMousePos()
{
    QScreen *screen = QApplication::primaryScreen();
    QCursor *cursor = new QCursor;

    //qDebug() << cursor->pos(screen);
}

void EditorWindow::printKey(int key, int status, int time)
{
    qDebug() <<  key  << " : " << status << " : " << time;
}

