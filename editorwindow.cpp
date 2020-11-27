#include "editorwindow.h"
#include "ui_editorwindow.h"

#include "input/DeviceFactory.h"

#include <QKeyEvent>
#include <QEvent>
#include <QScreen>
#include <QCursor>
#include <QtDebug>

#include "input/KeyboardAction.h"
#include "input/KeyboardEvent.h"

EditorWindow::EditorWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::EditorWindow)
{
    ui->setupUi(this);

    QHeaderView *header = ui->tableWidget->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableWidget->setHorizontalHeaderLabels({tr("Action"),
                                                tr("Start time [ms]")});

    connect(ui->recordButton, &QPushButton::clicked, [&](bool checked){
        isRecording = checked;
    });

    timer.start();

    mouse = DeviceFactory::makeMouse();
    mouse->setCallback([&](const MouseEvent &event) {
        if(isRecording)
            mouseEvent(event);
    });

    keyboard = DeviceFactory::makeKeyboard();
    keyboard->setCallback([&](const KeyboardEvent &event) {
        if(isRecording)
            kbEvent(event);
    });
}

EditorWindow::~EditorWindow()
{
    for(const auto & action : actions)
        delete action.first;

    DeviceFactory::removeInstances();
    delete ui;
}

void EditorWindow::addAction(Action *action, unsigned startTime, int index)
{
    actions.append(qMakePair(action, startTime));
    index = (index < 0) ? ui->tableWidget->rowCount() : index;

    ui->tableWidget->insertRow(index);

    QTableWidgetItem *name = new QTableWidgetItem(QString::fromStdString(action->name()));
    ui->tableWidget->setItem(index, 0, name);

    QTableWidgetItem *time = new QTableWidgetItem(QString("%1").arg(startTime));
    ui->tableWidget->setItem(index, 1, time);
}

void EditorWindow::kbEvent(const KeyboardEvent &event)
{
    qDebug() << "Key: " << event.code << ": " << (int)(event.status);

    KeyboardAction *action = new KeyboardAction(keyboard, event);
    addAction(action, timer.elapsed());
}

void EditorWindow::mouseEvent(const MouseEvent &event)
{
    qDebug() << "Mouse: " << QPoint(event.point.x, event.point.y)
                << ": " << (int)(event.key)
                << ": " << (int)(event.type);
}
