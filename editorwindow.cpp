#include "editorwindow.h"
#include "ui_editorwindow.h"

#include <QMessageBox>

#include "input/DeviceFactory.h"
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
                                                tr("Start time [ms] (from last)")});

    connect(ui->recordButton, &QPushButton::clicked, this, &EditorWindow::btnRecordPressed);
    connect(ui->playButton, &QPushButton::clicked, this, &EditorWindow::btnPlayPressed);

    connect(ui->gotoFirstButton, &QPushButton::clicked, this, &EditorWindow::btnFirstPressed);
    connect(ui->gotoPrevButton, &QPushButton::clicked, this, &EditorWindow::btnPrevPressed);
    connect(ui->gotoNextButton, &QPushButton::clicked, this, &EditorWindow::btnNextPressed);
    connect(ui->gotoEndButton, &QPushButton::clicked, this, &EditorWindow::btnLastPressed);

    connect(ui->actionExit, &QAction::triggered, this, &EditorWindow::close);
    connect(ui->action_About, &QAction::triggered, this, &EditorWindow::showAbout);

    timer.start();
    actionInvoker.setSingleShot(true);
    connect(&actionInvoker, &QTimer::timeout, this, &EditorWindow::invokeActions);

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

void EditorWindow::showAbout() const
{
    QMessageBox *about = new QMessageBox(QMessageBox::Information,
                                         tr("About"),
                                         tr("ActionCapture is Qt5 graphical application for "
                                            "recording and recreating user interactions "
                                            "such as mouse move/click and keyboard input.\n"
                                            "Project: https://github.com/Andrew2a1/ActionCapture"),
                                         QMessageBox::Ok,
                                         this->centralWidget());
    about->exec();
}

void EditorWindow::updatePlayStatus()
{
    const int current = ui->tableWidget->currentRow();
    const int total = ui->tableWidget->rowCount();
    const QString status = QString("Processing: %1/%2").arg(current+1).arg(total);

    if(current == -1)
        ui->statusbar->clearMessage();
    else
        ui->statusbar->showMessage(status);
}

void EditorWindow::btnRecordPressed(bool shouldRecord)
{
    ui->playButton->setChecked(false);
    btnPlayPressed(false);

    isRecording = shouldRecord;
    timer.restart();
}

void EditorWindow::btnNextPressed()
{
    int selected = ui->tableWidget->currentRow();
    ui->tableWidget->selectRow(selected + 1);
}

void EditorWindow::btnPrevPressed()
{
    int selected = ui->tableWidget->currentRow();
    ui->tableWidget->selectRow(selected - 1);
}

void EditorWindow::btnFirstPressed()
{
    ui->tableWidget->selectRow(0);
}

void EditorWindow::btnLastPressed()
{
    ui->tableWidget->selectRow(ui->tableWidget->rowCount() - 1);
}

void EditorWindow::btnPlayPressed(bool shouldPlay)
{
    if(ui->tableWidget->rowCount() <= 0)
    {
        ui->playButton->setChecked(false);
    }
    else if(shouldPlay)
    {
        int current = ui->tableWidget->currentRow();
        if(current < 0) {
            btnFirstPressed();
            current = 0;
        }

        updatePlayStatus();
        actionInvoker.start(actions[current].second);
    }
    else if(!shouldPlay)
    {
        actionInvoker.stop();
    }
}

void EditorWindow::invokeActions()
{
    int current = ui->tableWidget->currentRow();
    actions[current].first->run();
    updatePlayStatus();

    if(current < ui->tableWidget->rowCount() - 1)
    {
        actionInvoker.start(actions[current + 1].second);
        btnNextPressed();
    }
    else
    {
        ui->statusbar->clearMessage();
        ui->playButton->setChecked(false);
    }
}

void EditorWindow::kbEvent(const KeyboardEvent &event)
{
    KeyboardAction *action = new KeyboardAction(keyboard, event);
    addAction(action, timer.elapsed(), ui->tableWidget->currentRow());
    timer.restart();
}

void EditorWindow::mouseEvent(const MouseEvent &event)
{

}
