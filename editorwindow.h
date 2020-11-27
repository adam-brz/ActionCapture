#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <QMainWindow>
#include <QElapsedTimer>
#include <QTimer>

#include <QList>
#include <QPair>

#include <input/GlobalMouse.h>
#include <input/GlobalKeyboard.h>

#include "input/Action.h"
#include "input/KeyboardEvent.h"
#include "input/MouseEvent.h"

QT_BEGIN_NAMESPACE
namespace Ui { class EditorWindow; }
QT_END_NAMESPACE

class EditorWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::EditorWindow *ui;
    QElapsedTimer timer;
    QTimer actionInvoker;

    GlobalMouse *mouse;
    GlobalKeyboard *keyboard;

    QList<QPair<Action*, unsigned>> actions;
    bool isRecording = false;

public:
    EditorWindow(QWidget *parent = nullptr);
    ~EditorWindow();

    void addAction(Action* action, unsigned startTime, int index = -1);

private slots:
    void btnNextPressed();
    void btnPrevPressed();
    void btnFirstPressed();
    void btnLastPressed();
    void btnPlayPressed(bool shouldPlay);
    void btnRecordPressed(bool shouldRecord);

    void invokeActions();

private:
    void kbEvent(const KeyboardEvent &event);
    void mouseEvent(const MouseEvent &event);
};
#endif // EDITORWINDOW_H
