#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <QMainWindow>
#include <QElapsedTimer>
#include <QTimer>

#include <QList>

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

    GlobalMouse *mouse;
    GlobalKeyboard *keyboard;

    QList<Action*> actions;
    bool isRecording = false;

public:
    EditorWindow(QWidget *parent = nullptr);
    ~EditorWindow();

    void addAction(Action* action, int index = -1);

private slots:
    void showAbout() const;
    void updatePlayStatus(int current);

    void btnNextPressed();
    void btnPrevPressed();
    void btnFirstPressed();
    void btnLastPressed();
    void btnPlayPressed(bool shouldPlay);
    void btnRecordPressed(bool shouldRecord);

private:
    void kbEvent(const KeyboardEvent &event);
    void mouseEvent(const MouseEvent &event);
};
#endif // EDITORWINDOW_H
