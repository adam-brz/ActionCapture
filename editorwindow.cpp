#include "editorwindow.h"
#include "ui_editorwindow.h"

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

    connect(timer, &QTimer::timeout, this, &EditorWindow::printMousePos);
}

EditorWindow::~EditorWindow()
{
    delete ui;
}

void EditorWindow::keyPressEvent(QKeyEvent *event)
{
    qDebug() << event->timestamp() << " : " << Qt::Key(event->key());
}

void EditorWindow::printMousePos()
{
    QScreen *screen = QApplication::primaryScreen();
    QCursor *cursor = new QCursor;

    qDebug() << cursor->pos(screen);
}

