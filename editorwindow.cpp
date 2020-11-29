#include "editorwindow.h"
#include "ui_editorwindow.h"

#include <QMessageBox>
#include <QFileDialog>

#include "toolbox/SavableData.h"

#include "input/DeviceFactory.h"
#include "input/KeyboardAction.h"
#include "input/MouseAction.h"

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

    connect(ui->action_New, &QAction::triggered, this, &EditorWindow::newFile);
    connect(ui->action_Open, &QAction::triggered, this, &EditorWindow::askOpenFile);
    connect(ui->action_Save, &QAction::triggered, this, &EditorWindow::askSaveToFile);
    connect(ui->action_Save_as, &QAction::triggered, this, &EditorWindow::askSaveToFile);

    connect(ui->action_About, &QAction::triggered, this, &EditorWindow::showAbout);
    connect(ui->actionExit, &QAction::triggered, this, &EditorWindow::close);

    timer.start();
    connect(ui->actionTable, &ActionTable::runUpdated, this, &EditorWindow::updatePlayStatus);

    mouse = DeviceFactory::makeMouse();
    mouse->setCallback([&](const MouseEvent &event) {mouseEvent(event);});

    keyboard = DeviceFactory::makeKeyboard();
    keyboard->setCallback([&](const KeyboardEvent &event) {kbEvent(event);});

    ui->actionTable->setMouse(mouse);
    ui->actionTable->setKeyboard(keyboard);
}

EditorWindow::~EditorWindow()
{    
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
        stopPlaying();
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
        stopRecording();
        ui->actionTable->runActions();
    }
    else if(!shouldPlay) {
        ui->actionTable->stopRunning();
    }
}

void EditorWindow::newFile()
{
    stopPlaying();
    stopRecording();

    ui->actionTable->clearActions();
}

void EditorWindow::askSaveToFile()
{
    QString name = QFileDialog::getSaveFileName(this, tr("Open saved actions"),
                                        ".", tr("Action Capture (*.actc)"));

    if(!name.isEmpty()) {
        saveToFile(name);
    }
}

void EditorWindow::askOpenFile()
{
    QString name = QFileDialog::getOpenFileName(this, tr("Open saved actions"),
                                                ".", tr("Action Capture (*.actc)"));

    if(!name.isEmpty()) {
        openFile(name);
    }
}


bool EditorWindow::openFile(const QString &filename)
{
    QFile saveFile(filename);
    SavableData savable;

    saveFile.open(QIODevice::ReadOnly);

    if(!(saveFile.read(4) == QString("ACTC").toLocal8Bit()))
        return false;

    QByteArray data = saveFile.readAll();

    savable.reserve(data.size());
    savable.add(RawBytesConst(data.data()), data.size());

    ui->actionTable->restore(&savable);

    saveFile.close();
    return true;
}

bool EditorWindow::saveToFile(const QString &filename)
{
    SavableData *savable = ui->actionTable->save();

    QFile saveFile(filename);
    saveFile.open(QIODevice::WriteOnly);

    if(!saveFile.isWritable())
        return false;

    saveFile.write("ACTC", 4);
    saveFile.write((const char*)(savable->getRaw()), savable->size());
    saveFile.close();

    delete savable;
    return true;
}

void EditorWindow::stopPlaying()
{
    ui->actionTable->stopRunning();
    ui->playButton->setChecked(false);
    btnPlayPressed(false);
}

void EditorWindow::stopRecording()
{
    ui->recordButton->setChecked(false);
    btnRecordPressed(false);
}

void EditorWindow::kbEvent(const KeyboardEvent &event)
{
    if(!isRecording)
        return;

    Action *action = new KeyboardAction(keyboard, event);
    action->setStartTime(timer.elapsed());
    addAction(action, ui->actionTable->current());
    timer.restart();
}

void EditorWindow::mouseEvent(const MouseEvent &event)
{
    if(!isRecording)
        return;

    Action *action = new MouseAction(mouse, event);
    action->setStartTime(timer.elapsed());
    addAction(action, ui->actionTable->current());
    timer.restart();
}
