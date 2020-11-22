#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include <input/GlobalMouse.h>
#include <input/GlobalKeyboard.h>

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

    GlobalMouse *mouse;
    GlobalKeyboard *keyboard;

public:
    EditorWindow(QWidget *parent = nullptr);
    ~EditorWindow();

private:
    void kbEvent(const KeyboardEvent &event);
    void mouseEvent(const MouseEvent &event);

};
#endif // EDITORWINDOW_H
