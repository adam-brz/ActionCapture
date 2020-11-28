#include "editorwindow.h"
#include "ui_editorwindow.h"

#include <QMessageBox>
#include <QtDebug>

#include "input/DeviceFactory.h"
#include "input/KeyboardAction.h"
#include "input/KeyboardEvent.h"

EditorWindow::EditorWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::EditorWindow)
{
    ui->setupUi(this);

    connect(ui->recordButton, &QPushButton::clicked, this, &EditorWindow::btnRecordPressed);
    connect(ui->playButton, &QPushButton::clicked, this, &EditorWindow::btnPlayPressed);

    connect(ui->gotoFirstButton, &QPushButton::clicked, this, &EditorWindow::btnFirstPressed);
    connect(ui->gotoPrevButton, &QPushButton::clicked, this, &EditorWindow::btnPrevPressed);
    connect(ui->gotoNextButton, &QPushButton::clicked, this, &EditorWindow::btnNextPressed);
    connect(ui->gotoEndButton, &QPushButton::clicked, this, &EditorWindow::btnLastPressed);

    connect(ui->actionExit, &QAction::triggered, this, &EditorWindow::close);
    connect(ui->action_About, &QAction::triggered, this, &EditorWindow::showAbout);

    connect(ui->actionTable, &ActionTable::runUpdated, this, &EditorWindow::updatePlayStatus);
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
        delete action;

    DeviceFactory::removeInstances();
    delete ui;
}

void EditorWindow::addAction(Action *action, int index)
{
    ui->actionTable->addAction(action, index);
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

void EditorWindow::updatePlayStatus(int current)
{
    const int total = ui->actionTable->size();
    const QString status = QString("Running: %1/%2").arg(current+1).arg(total);

    if(current == -1 || current+1 == total) {
        ui->statusbar->clearMessage();
        ui->playButton->setChecked(false);
    }
    else {
        ui->statusbar->showMessage(status);
    }
}

void EditorWindow::btnRecordPressed(bool shouldRecord)
{
    if(shouldRecord) {
        ui->actionTable->stopRunning();
        ui->playButton->setChecked(false);
        btnPlayPressed(false);
    }

    isRecording = shouldRecord;
    timer.restart();
}

void EditorWindow::btnNextPressed()
{
    int selected = ui->actionTable->current();
    ui->actionTable->select(selected + 1);
}

void EditorWindow::btnPrevPressed()
{
    int selected = ui->actionTable->current();
    ui->actionTable->select(selected - 1);
}

void EditorWindow::btnFirstPressed()
{
    ui->actionTable->select(0);
}

void EditorWindow::btnLastPressed()
{
    ui->actionTable->select(ui->actionTable->size() - 1);
}

void EditorWindow::btnPlayPressed(bool shouldPlay)
{
    if(ui->actionTable->size() <= 0) {
        ui->playButton->setChecked(false);
    }
    else if(shouldPlay) {
        ui->recordButton->setChecked(false);
        btnRecordPressed(false);
        ui->actionTable->runActions();
    }
    else if(!shouldPlay) {
        ui->actionTable->stopRunning();
    }
}

void EditorWindow::kbEvent(const KeyboardEvent &event)
{
    KeyboardAction *action = new KeyboardAction(keyboard, event);
    action->setStartTime(timer.elapsed());
    addAction(action, ui->actionTable->current());
    timer.restart();
}

void EditorWindow::mouseEvent(const MouseEvent &event)
{

}
